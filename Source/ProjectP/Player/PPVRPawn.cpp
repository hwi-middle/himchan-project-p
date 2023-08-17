// Fill out your copyright notice in the Description page of Project Settings.


#include "PPVRPawn.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "PPMovementData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MotionControllerComponent.h"
#include "PPVRHand.h"

#include "EnhancedInput/Public/InputActionValue.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectP/Prop/Weapon/PPGunBase.h"

#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPVRPawn::APPVRPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	RootComponent = VROrigin;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	Camera->SetupAttachment(VROrigin);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	MovementData = FPPConstructorHelper::FindAndGetObject<UPPMovementData>(TEXT("/Script/ProjectP.PPMovementData'/Game/DataAssets/Player/PlayerData.PlayerData'"), EAssertionLevel::Check);
	InputMappingContext = MovementData->InputMappingContext;
	MoveAction = MovementData->MoveAction;
	TurnAction = MovementData->TurnAction;
	SprintAction = MovementData->SprintAction;
	GrabLeftAction = MovementData->GrabLeftAction;
	GrabRightAction = MovementData->GrabRightAction;
	IndexCurlLeftAction = MovementData->IndexCurlLeftAction;
	IndexCurlRightAction = MovementData->IndexCurlRightAction;
	PointLeftAction = MovementData->PointLeftAction;
	PointRightAction = MovementData->PointRightAction;
	ThumbUpLeftAction = MovementData->ThumbUpLeftAction;
	ThumbUpRightAction = MovementData->ThumbUpRightAction;
	LeftXButtonPressAction = MovementData->LeftXButtonPressAction;
	RightBButtonPressAction = MovementData->RightBButtonPressAction;
	
	MoveSpeed = MovementData->MoveSpeed;
	SnapTurnDegrees = MovementData->SnapTurnDegrees;
	WidgetInteractionDistance = MovementData->WidgetInteractionDistance;
}

// Called when the game starts or when spawned
void APPVRPawn::BeginPlay()
{
	Super::BeginPlay();
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	InitVROrigin();
	InitVRHands();
}

// Called every frame
void APPVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APPVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	const APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	SubSystem->ClearAllMappings();
	SubSystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APPVRPawn::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APPVRPawn::DisableSprint);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &APPVRPawn::Turn);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APPVRPawn::ToggleSprint);

	EnhancedInputComponent->BindAction(GrabLeftAction, ETriggerEvent::Triggered, this, &APPVRPawn::GrabLeft);
	EnhancedInputComponent->BindAction(GrabLeftAction, ETriggerEvent::Completed, this, &APPVRPawn::CancelOrCompleteGrabLeft);
	EnhancedInputComponent->BindAction(GrabLeftAction, ETriggerEvent::Canceled, this, &APPVRPawn::CancelOrCompleteGrabLeft);
	EnhancedInputComponent->BindAction(GrabRightAction, ETriggerEvent::Triggered, this, &APPVRPawn::GrabRight);
	EnhancedInputComponent->BindAction(GrabRightAction, ETriggerEvent::Completed, this, &APPVRPawn::CancelOrCompleteGrabRight);
	EnhancedInputComponent->BindAction(GrabRightAction, ETriggerEvent::Canceled, this, &APPVRPawn::CancelOrCompleteGrabRight);

	EnhancedInputComponent->BindAction(IndexCurlLeftAction, ETriggerEvent::Triggered, this, &APPVRPawn::IndexCurlLeft);
	EnhancedInputComponent->BindAction(IndexCurlLeftAction, ETriggerEvent::Completed, this, &APPVRPawn::CancelOrCompleteIndexCurlLeft);
	EnhancedInputComponent->BindAction(IndexCurlLeftAction, ETriggerEvent::Canceled, this, &APPVRPawn::CancelOrCompleteIndexCurlLeft);
	EnhancedInputComponent->BindAction(IndexCurlRightAction, ETriggerEvent::Triggered, this, &APPVRPawn::IndexCurlRight);
	EnhancedInputComponent->BindAction(IndexCurlRightAction, ETriggerEvent::Completed, this, &APPVRPawn::CancelOrCompleteIndexCurlRight);
	EnhancedInputComponent->BindAction(IndexCurlRightAction, ETriggerEvent::Canceled, this, &APPVRPawn::CancelOrCompleteIndexCurlRight);

	EnhancedInputComponent->BindAction(PointLeftAction, ETriggerEvent::Triggered, this, &APPVRPawn::PointLeft);
	EnhancedInputComponent->BindAction(PointLeftAction, ETriggerEvent::Completed, this, &APPVRPawn::CompletePointLeft);
	EnhancedInputComponent->BindAction(PointLeftAction, ETriggerEvent::Canceled, this, &APPVRPawn::PointLeft);
	EnhancedInputComponent->BindAction(PointRightAction, ETriggerEvent::Triggered, this, &APPVRPawn::PointRight);
	EnhancedInputComponent->BindAction(PointRightAction, ETriggerEvent::Completed, this, &APPVRPawn::CompletePointRight);
	EnhancedInputComponent->BindAction(PointRightAction, ETriggerEvent::Canceled, this, &APPVRPawn::PointRight);

	EnhancedInputComponent->BindAction(ThumbUpLeftAction, ETriggerEvent::Triggered, this, &APPVRPawn::ThumbUpLeft);
	EnhancedInputComponent->BindAction(ThumbUpLeftAction, ETriggerEvent::Completed, this, &APPVRPawn::CompleteThumbUpLeft);
	EnhancedInputComponent->BindAction(ThumbUpLeftAction, ETriggerEvent::Canceled, this, &APPVRPawn::ThumbUpLeft);
	EnhancedInputComponent->BindAction(ThumbUpRightAction, ETriggerEvent::Triggered, this, &APPVRPawn::ThumbUpRight);
	EnhancedInputComponent->BindAction(ThumbUpRightAction, ETriggerEvent::Completed, this, &APPVRPawn::CompleteThumbUpRight);
	EnhancedInputComponent->BindAction(ThumbUpRightAction, ETriggerEvent::Canceled, this, &APPVRPawn::ThumbUpRight);
	EnhancedInputComponent->BindAction(LeftXButtonPressAction, ETriggerEvent::Started, this, &APPVRPawn::ToggleWidgetInteraction);
	EnhancedInputComponent->BindAction(RightBButtonPressAction, ETriggerEvent::Started, this, &APPVRPawn::ToggleFlash);
}

void APPVRPawn::InitVROrigin()
{
	const float DistanceToFloor = GetActorLocation().Z;
	VROrigin->SetRelativeLocation(FVector{0, 0, -DistanceToFloor});
}

void APPVRPawn::InitVRHands()
{
	const FTransform IdentityTransform;
	const FAttachmentTransformRules AttachRule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	LeftHand = GetWorld()->SpawnActorDeferred<APPVRHand>(APPVRHand::StaticClass(), IdentityTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	ensure(LeftHand);
	LeftHand->SetHandType(EControllerHand::Left);
	LeftHand->FinishSpawning(IdentityTransform);
	LeftHand->AttachToComponent(VROrigin, AttachRule);
	
	RightHand = GetWorld()->SpawnActorDeferred<APPVRHand>(APPVRHand::StaticClass(), IdentityTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	ensure(RightHand);
	RightHand->SetHandType(EControllerHand::Right);
	RightHand->FinishSpawning(IdentityTransform);
	RightHand->AttachToComponent(VROrigin, AttachRule);
}

void APPVRPawn::Move(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();

	FVector ActorUp = GetActorUpVector();
	FVector CameraForward = Camera->GetForwardVector();

	CameraForward -= UKismetMathLibrary::ProjectVectorOnToVector(CameraForward, ActorUp);
	CameraForward.Normalize();

	AddActorWorldOffset(FVector(CameraForward * InputVector.Y * MoveSpeed), true);

	FVector CameraRight = Camera->GetRightVector();

	CameraRight -= UKismetMathLibrary::ProjectVectorOnToVector(CameraRight, ActorUp);
	CameraRight.Normalize();

	AddActorWorldOffset(FVector(CameraRight * InputVector.X * MoveSpeed), true);
}

void APPVRPawn::Turn(const FInputActionValue& Value)
{
	const float InputValue = Value.Get<float>();

	const FVector CameraLocation = Camera->GetComponentLocation();
	const FTransform CameraRelativeTransform = Camera->GetRelativeTransform();

	AddActorWorldRotation(FRotator(0.f, InputValue > 0 ? SnapTurnDegrees : -SnapTurnDegrees, 0.f));
	const FTransform ChangedActorTransform = GetActorTransform();
	const FVector TransformedLocation = UKismetMathLibrary::ComposeTransforms(CameraRelativeTransform, ChangedActorTransform).GetLocation();
	FVector InversedDirection = CameraLocation - TransformedLocation;
	InversedDirection.Z = 0;

	SetActorLocation(GetActorLocation() + InversedDirection);
}

void APPVRPawn::GrabLeft(const FInputActionValue& Value)
{
	const float Alpha = Value.Get<float>();
	LeftHand->SetPoseAlphaGrasp(Alpha);

	UPPVRGrabComponent* HeldComponent = LeftHand->GetHeldComponent();
	static constexpr float GrabThreshold = 0.2f;
	if (HeldComponent && Alpha < GrabThreshold)
	{
		LeftHand->HandleRelease();
	}
	else if (!HeldComponent && Alpha > GrabThreshold)
	{
		LeftHand->HandleGrab();
	}
}

void APPVRPawn::GrabRight(const FInputActionValue& Value)
{
	const float Alpha = Value.Get<float>();
	RightHand->SetPoseAlphaGrasp(Alpha);

	UPPVRGrabComponent* HeldComponent = RightHand->GetHeldComponent();
	static constexpr float GrabThreshold = 0.2f;
	if (HeldComponent && Alpha < GrabThreshold)
	{
		RightHand->HandleRelease();
	}
	else if (!HeldComponent && Alpha > GrabThreshold)
	{
		RightHand->HandleGrab();
	}
}

void APPVRPawn::IndexCurlLeft(const FInputActionValue& Value)
{
	const float Alpha = Value.Get<float>();
	LeftHand->SetPoseAlphaIndexCurl(Alpha);
	UPPVRGrabComponent* HeldComponent = LeftHand->GetHeldComponent();
	if (HeldComponent)
	{
		APPGunBase* Weapon = Cast<APPGunBase>(HeldComponent->GetOuter());
		if (Weapon)
		{
			Weapon->OnFire();
		}
	}
}

void APPVRPawn::IndexCurlRight(const FInputActionValue& Value)
{
	const float Alpha = Value.Get<float>();
	RightHand->SetPoseAlphaIndexCurl(Alpha);
	UPPVRGrabComponent* HeldComponent = RightHand->GetHeldComponent();

	static constexpr float ShootThreshold = 0.2f;
	if (HeldComponent)
	{
		APPGunBase* Weapon = Cast<APPGunBase>(HeldComponent->GetOuter());
		if (Weapon && Alpha > ShootThreshold)
		{
			Weapon->OnFire();
		}
	}
}

void APPVRPawn::PointLeft(const FInputActionValue& Value)
{
	LeftHand->SetPoseAlphaPoint(0);
}

void APPVRPawn::PointRight(const FInputActionValue& Value)
{
	RightHand->SetPoseAlphaPoint(0);
}

void APPVRPawn::ThumbUpLeft(const FInputActionValue& Value)
{
	LeftHand->SetPoseAlphaThumbUp(0);
}

void APPVRPawn::ThumbUpRight(const FInputActionValue& Value)
{
	RightHand->SetPoseAlphaThumbUp(0);
}

void APPVRPawn::DisableSprint(const FInputActionValue& Value)
{
	if (MoveSpeed == MovementData->SprintSpeed)
	{
		MoveSpeed = MovementData->MoveSpeed;
	}
}

void APPVRPawn::ToggleSprint(const FInputActionValue& Value)
{
	MoveSpeed == MovementData->MoveSpeed ? MoveSpeed = MovementData->SprintSpeed : MoveSpeed = MovementData->MoveSpeed;
}

void APPVRPawn::ToggleFlash(const FInputActionValue& Value)
{
	UPPVRGrabComponent* LeftHeldComponent = LeftHand->GetHeldComponent();
	UPPVRGrabComponent* RightHeldComponent = RightHand->GetHeldComponent();
	if (LeftHeldComponent)
	{
		APPGunBase* Weapon = Cast<APPGunBase>(LeftHeldComponent->GetOuter());
		if (Weapon)
		{
			Weapon->ToggleFlash();
		}
	}
	else if(RightHeldComponent)
	{
		APPGunBase* Weapon = Cast<APPGunBase>(RightHeldComponent->GetOuter());
		if (Weapon)
		{
			Weapon->ToggleFlash();
		}
	}
}

void APPVRPawn::ToggleWidgetInteraction(const FInputActionValue& Value)
{
	// 나중에 주로 사용하는 손 바꾸기 구현되면 수정 예정
	LeftHand->WidgetInteractionToggle(WidgetInteractionDistance);
}

void APPVRPawn::CancelOrCompleteGrabLeft()
{
	LeftHand->SetPoseAlphaGrasp(0);
	LeftHand->HandleRelease();
}

void APPVRPawn::CancelOrCompleteGrabRight()
{
	RightHand->SetPoseAlphaGrasp(0);
	RightHand->HandleRelease();
}

void APPVRPawn::CancelOrCompleteIndexCurlLeft()
{
	LeftHand->SetPoseAlphaIndexCurl(0);
	UPPVRGrabComponent* HeldComponent = LeftHand->GetHeldComponent();

	if (HeldComponent)
	{
		APPGunBase* Weapon = Cast<APPGunBase>(HeldComponent->GetOuter());
		if (Weapon)
		{
			Weapon->StopFire();
		}
	}
}

void APPVRPawn::CancelOrCompleteIndexCurlRight()
{
	RightHand->SetPoseAlphaIndexCurl(0);
	UPPVRGrabComponent* HeldComponent = RightHand->GetHeldComponent();

	if (HeldComponent)
	{
		APPGunBase* Weapon = Cast<APPGunBase>(HeldComponent->GetOuter());
		if (Weapon)
		{
			Weapon->StopFire();
		}
	}
}

void APPVRPawn::CompletePointLeft()
{
	LeftHand->SetPoseAlphaPoint(1);
}

void APPVRPawn::CompletePointRight()
{
	RightHand->SetPoseAlphaPoint(1);
}

void APPVRPawn::CompleteThumbUpLeft()
{
	LeftHand->SetPoseAlphaThumbUp(1);
}

void APPVRPawn::CompleteThumbUpRight()
{
	RightHand->SetPoseAlphaThumbUp(1);
}
