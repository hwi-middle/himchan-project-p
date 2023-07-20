// Fill out your copyright notice in the Description page of Project Settings.


#include "PPVRPawn.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

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

	InputMappingContext = FPPConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/15-Basic-Movement/Input/IMC_DefaultVR.IMC_DefaultVR'"));
	ensure(InputMappingContext);
	MoveAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/IA_VRMove.IA_VRMove'"));
	TurnAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/IA_VRTurn.IA_VRTurn'"));
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

}

void APPVRPawn::Move(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();

	FVector ActorUp = GetActorUpVector();
	FVector CameraForward = Camera->GetForwardVector();

	CameraForward -= UKismetMathLibrary::ProjectVectorOnToVector(CameraForward, ActorUp);
	CameraForward.Normalize();

	AddActorWorldOffset(FVector(CameraForward * InputVector.Y * 3));

	FVector CameraRight = Camera->GetRightVector();

	CameraRight -= UKismetMathLibrary::ProjectVectorOnToVector(CameraRight, ActorUp);
	CameraRight.Normalize();

	AddActorWorldOffset(FVector(CameraRight * InputVector.X * 3));
}

void APPVRPawn::Turn(const FInputActionValue& Value)
{
	const float InputValue = Value.Get<float>();
	float SnapTurnDegrees = 45.f;

	if (InputValue < 0)
	{
		SnapTurnDegrees *= -1;
	}

	const FVector CameraLocation = Camera->GetComponentLocation();
	const FTransform CameraRelativeTransform = Camera->GetRelativeTransform();

	AddActorWorldRotation(FRotator(0.f, SnapTurnDegrees, 0.f));
	const FTransform ChangedActorTransform = GetActorTransform();
	const FVector TransformedLocation = UKismetMathLibrary::ComposeTransforms(CameraRelativeTransform, ChangedActorTransform).GetLocation();
	const FVector InversedDirection = CameraLocation - TransformedLocation;

	SetActorLocation(GetActorLocation() + InversedDirection);
}
