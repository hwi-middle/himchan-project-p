// Fill out your copyright notice in the Description page of Project Settings.

#include "PPVRHand.h"

#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "ProjectP/Animation/PPVRHandAnimInstance.h"
#include "ProjectP/UI/TestOnly/PPDebugWidget.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPDrawLineHelper.h"

// Sets default values
APPVRHand::APPVRHand()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GripRadius = 6.f;
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	RootComponent = MotionController;
	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(MotionController);
	HandAnimInstanceClass = FPPConstructorHelper::FindAndGetClass<UPPVRHandAnimInstance>(TEXT("/Game/15-Basic-Movement/Animation/Hand/ABP_VRHand.ABP_VRHand_C"), EAssertionLevel::Check);
	HandMesh->SetAnimInstanceClass(HandAnimInstanceClass);

	HandWidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	HandWidgetInteraction->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	HandWidgetInteraction->SetupAttachment(MotionController);
	HandWidgetInteraction->TraceChannel = ECC_Visibility;
	HandWidgetInteraction->InteractionDistance = 0.0f;
	
	// Test Only
	DebugWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DebugWidget"));
	DebugWidgetComponent->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPDebugWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/30-Level-Design/TestOnlyBlueprint/DebugViewWidget.DebugViewWidget_C'"), EAssertionLevel::Check));
	DebugWidgetComponent->SetMaterial(
		0, FPPConstructorHelper::FindAndGetObject<UMaterialInterface>(TEXT("/Script/Engine.MaterialInstanceConstant'/Engine/EngineMaterials/Widget3DPassThrough_Translucent.Widget3DPassThrough_Translucent'"), EAssertionLevel::Check));
	DebugWidgetComponent->SetupAttachment(MotionController);
	//
}

// Called when the game starts or when spawned
void APPVRHand::BeginPlay()
{
	Super::BeginPlay();
	InitHand();
	InitHandMeshRelativeTransform = HandMesh->GetRelativeTransform();
}

// Called every frame
void APPVRHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!HandWidgetInteraction->IsActive() || HandWidgetInteraction->InteractionDistance <= 0.0f)
	{
		return;
	}

	FHitResult HandWidgetHitResult = HandWidgetInteraction->GetLastHitResult();

	UWidgetComponent* HoveredWidget = HandWidgetInteraction->GetHoveredWidgetComponent();
	if (HoveredWidget)
	{
		FPPDrawLineHelper::DrawSphere(GetWorld(), HandWidgetHitResult.ImpactPoint, 2.5f, 12, FColor::Red, false, -1, 0, HandWidgetInteraction->DebugSphereLineThickness);
		FPPDrawLineHelper::DrawLine(GetWorld(), HandWidgetHitResult.TraceStart, HandWidgetHitResult.ImpactPoint, FColor::Red, false, -1, 0, HandWidgetInteraction->DebugLineThickness);
	}
	else
	{
		float Distance = HandWidgetInteraction->InteractionDistance;
		FPPDrawLineHelper::DrawLine(GetWorld(), GetActorLocation(), GetActorLocation() + HandWidgetInteraction->GetForwardVector() * Distance, FColor::Red, false, -1, 0, HandWidgetInteraction->DebugLineThickness);
	}
}

UPPVRGrabComponent* APPVRHand::FindGrabComponentNearby()
{
	FVector GripPos = MotionController->GetComponentLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_GIMMICK));
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;

	const bool Result = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		GripPos,
		GripPos,
		GripRadius,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OUT HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f
	);

	return Result ? HitResult.GetActor()->FindComponentByClass<UPPVRGrabComponent>() : nullptr;
}

void APPVRHand::HandleGrab()
{
	if (UPPVRGrabComponent* GrabComponent = FindGrabComponentNearby())
	{
		HeldComponent = GrabComponent->TryGrab(this) ? GrabComponent : nullptr;
	}
}

void APPVRHand::HandleRelease()
{
	if (HeldComponent)
	{
		HeldComponent->TryRelease();
		HeldComponent = nullptr;
	}
}

void APPVRHand::SetPoseAlphaGrasp(const float Value)
{
	AnimInstance->SetPoseAlphaGrasp(Value);
}

void APPVRHand::SetPoseAlphaIndexCurl(const float Value)
{
	AnimInstance->SetPoseAlphaIndexCurl(Value);
	if (HandWidgetInteraction->InteractionDistance > 0.0f)
	{
		static constexpr float WidgetInteractionThreshold = 0.2f;
		Value > WidgetInteractionThreshold ? this->HandWidgetInteraction->PressPointerKey(TEXT("LeftMouseButton")) : this->HandWidgetInteraction->ReleasePointerKey(TEXT("LeftMouseButton"));
	}
}

void APPVRHand::SetPoseAlphaThumbUp(const float Value)
{
	AnimInstance->SetPoseAlphaThumbUp(Value);
}

void APPVRHand::SetPoseAlphaPoint(const float Value)
{
	AnimInstance->SetPoseAlphaPoint(Value);
}

void APPVRHand::WidgetInteractionToggle(const float Value)
{
	// SetActive로 제어하려니 작동이 제대로 안되서 크기 조정으로 대체
	bool bIsActivated = abs(HandWidgetInteraction->InteractionDistance - Value) <= KINDA_SMALL_NUMBER;
	HandWidgetInteraction->InteractionDistance = bIsActivated ? 0.f : Value;	
}

void APPVRHand::InitHand()
{
	MotionController->SetTrackingSource(HandType);

	FString Path;
	switch (HandType)
	{
	case EControllerHand::Left:
		HandMesh->SetRelativeRotation(FRotator(0.f, 180.f, 90.f));
		Path = TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'");
		
		SetupDebugWidget();
		break;
	case EControllerHand::Right:
		HandMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
		Path = TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'");
		DebugWidgetComponent->DestroyComponent();
		break;
	default:
		checkNoEntry();
	}

	USkeletalMesh* HandMeshObject = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, *Path));
	HandMesh->SetSkeletalMesh(HandMeshObject);
	AnimInstance = Cast<UPPVRHandAnimInstance>(HandMesh->GetAnimInstance());
	AnimInstance->SetIsMirror(HandType == EControllerHand::Left);
}

void APPVRHand::ResetHandMesh()
{
	HandMesh->AttachToComponent(MotionController, FAttachmentTransformRules::KeepWorldTransform);
	HandMesh->SetRelativeTransform(InitHandMeshRelativeTransform, false, nullptr, ETeleportType::TeleportPhysics);
}

void APPVRHand::DisableWidgetComponent() const
{
	HandWidgetInteraction->InteractionDistance = 0.0f;
	HandWidgetInteraction->SetActive(false);
}

void APPVRHand::SetupWidgetComponent(const float Value)
{
	HandWidgetInteraction->InteractionDistance = Value;
	HandWidgetInteraction->SetActive(true);
}

void APPVRHand::SetupDebugWidget()
{
	// 히히 매직넘버 발사
	DebugWidgetComponent->SetWorldScale3D(FVector(1.0f, 0.01f, 0.01f));
	DebugWidgetComponent->SetRelativeLocation(FVector(0.0f, -7.0f, 4.0f));
	DebugWidgetComponent->SetRelativeRotation(FRotator(180.0f, 90.0f, 90.0f));
	DebugWidgetComponent->SetDrawSize(FVector2d(1920.0f, 1080.0f));
}
