// Fill out your copyright notice in the Description page of Project Settings.


#include "PPVRHand.h"

#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPVRHand::APPVRHand()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	RootComponent = MotionController;
	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(MotionController);
}

// Called when the game starts or when spawned
void APPVRHand::BeginPlay()
{
	Super::BeginPlay();
	InitHand();
}

// Called every frame
void APPVRHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		SetActorLabel(TEXT("LeftHand"));
		break;
	case EControllerHand::Right:
		HandMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));	
		Path = TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'");
		SetActorLabel(TEXT("RightHand"));
		break;
	default:
		checkNoEntry();
	}

	USkeletalMesh* HandMeshObject= Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, *Path));
	check(HandMeshObject)
	HandMesh->SetSkeletalMesh(HandMeshObject);
}
