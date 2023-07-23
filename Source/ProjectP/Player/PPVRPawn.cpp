// Fill out your copyright notice in the Description page of Project Settings.


#include "PPVRPawn.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "PPMovementData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MotionControllerComponent.h"

#include "EnhancedInput/Public/InputActionValue.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "Kismet/KismetMathLibrary.h"

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

	MovementData = FPPConstructorHelper::FindAndGetObject<UPPMovementData>(TEXT("/Script/ProjectP.PPMovementData'/Game/15-Basic-Movement/Input/PlayerData.PlayerData'"), EAssertionLevel::Check);
	InputMappingContext = MovementData->InputMappingContext;
	MoveAction = MovementData->MoveAction;
	TurnAction = MovementData->TurnAction;
	SprintAction = MovementData->SprintAction;
	
	MoveSpeed = MovementData->MoveSpeed;
	SnapTurnDegrees = MovementData->SnapTurnDegrees;

	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	LeftMotionController->SetupAttachment(VROrigin);
	LeftMotionController->bDisplayDeviceModel= true;
	LeftMotionController->SetTrackingSource(EControllerHand::Left);
	
	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	RightMotionController->SetupAttachment(VROrigin);
	RightMotionController->bDisplayDeviceModel= true;
	RightMotionController->SetTrackingSource(EControllerHand::Right);
}

// Called when the game starts or when spawned
void APPVRPawn::BeginPlay()
{
	Super::BeginPlay();
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
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
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &APPVRPawn::Turn);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APPVRPawn::EnableSprint);
	/*
	 *	현재 구현: SprintAction의 입력 여부에 따라 달리기 전환
	 *	IF 한번 누르면 이동 입력이 끝나기 전 까지 달리기 상태를 유지한다면 아래 바인딩을 MoveAction으로 변경
	 */ 
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APPVRPawn::DisableSprint);
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
	const FVector InversedDirection = CameraLocation - TransformedLocation;

	SetActorLocation(GetActorLocation() + InversedDirection);
}

void APPVRPawn::EnableSprint(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("%f"), MoveSpeed);
	MoveSpeed = MovementData->SprintSpeed;
}

void APPVRPawn::DisableSprint(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("%f"), MoveSpeed);
	MoveSpeed = MovementData->MoveSpeed;
}
