// Fill out your copyright notice in the Description page of Project Settings.


#include "PPCharacterPlayer.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PPCharacterControlData.h"

// Sets default values
APPCharacterPlayer::APPCharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = true;

	// Input
	// GamePad는 연결 테스트용. IA와 IMC에 기기 입력값 매핑은 해놓은 상태라 상의 후 적절하게 이름 변경 예정
	static ConstructorHelpers::FObjectFinder<UPPCharacterControlData> GamePadDataRef(TEXT("/Script/ProjectP.PPCharacterControlData'/Game/PlayerControlTest/Input/PPC_GamePad.PPC_GamePad'"));
	if(GamePadDataRef.Object)
	{
		PlayerControlData = GamePadDataRef.Object;
	}
	static  ConstructorHelpers::FObjectFinder<UInputAction> GamePadMovementInputActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerControlTest/Input/Actions/IA_VRMove_GamePad.IA_VRMove_GamePad'"));
	if(GamePadMovementInputActionRef.Object)
	{
		PlayerMovementAction = GamePadMovementInputActionRef.Object;
	}
	static  ConstructorHelpers::FObjectFinder<UInputAction> GamePadRunActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerControlTest/Input/Actions/IA_VR_SwitchRun.IA_VR_SwitchRun'"));
	if(GamePadMovementInputActionRef.Object)
	{
		PlayerRunAction = GamePadRunActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> GamePadQuickRotationActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerControlTest/Input/Actions/IA_VR_QuickRotation.IA_VR_QuickRotation'"));
	if(GamePadQuickRotationActionRef.Object)
	{
		PlayerQuickRotationAction = GamePadQuickRotationActionRef.Object;
	}
}

void APPCharacterPlayer::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupCharacterControlData(PlayerControlData);
}

// Called to bind functionality to input
void APPCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if(EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(PlayerMovementAction, ETriggerEvent::Triggered, this, &APPCharacterPlayer::PlayerMovement);
		EnhancedInputComponent->BindAction(PlayerRunAction, ETriggerEvent::Triggered, this, &APPCharacterPlayer::PlayerIsRunning);
		EnhancedInputComponent->BindAction(PlayerQuickRotationAction, ETriggerEvent::Started, this, &APPCharacterPlayer::PlayerQuickRotation);
	}
}

void APPCharacterPlayer::SetupCharacterControlData(const UPPCharacterControlData* CharacterControlData)
{
	Super::SetupCharacterControlData(CharacterControlData);
	const APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		const UInputMappingContext* NewMappingContext = CharacterControlData->InputMappingContext;
		if(NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}
}

void APPCharacterPlayer::PlayerMovement(const FInputActionValue& Value)
{
	const FVector2D MovementVector2D = Value.Get<FVector2D>();
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(bIsRunning)
	{
		AddMovementInput(ForwardDirection, MovementVector2D.X * RunSpeed);
		AddMovementInput(RightDirection, MovementVector2D.Y * RunSpeed);
		UE_LOG(LogTemp, Log, TEXT("달리기"));
	}
	else
	{
		AddMovementInput(ForwardDirection, MovementVector2D.X * WalkSpeed);
		AddMovementInput(RightDirection, MovementVector2D.Y * WalkSpeed);
		UE_LOG(LogTemp, Log, TEXT("걷기"));
	}
	bIsRunning = false;
}

void APPCharacterPlayer::PlayerIsRunning(const FInputActionValue& Value)
{
	bIsRunning = true;
}

void APPCharacterPlayer::PlayerQuickRotation(const FInputActionValue& Value)
{
	const FVector2D RotationVector2D = Value.Get<FVector2D>();
	FRotator Rotation = Controller->GetControlRotation();
	
	const float QuickRotateDirection = RotationVector2D.X;
	UE_LOG(LogTemp, Log, TEXT("우측 아날로그 스틱 값: %f"), QuickRotateDirection);
	
	if(QuickRotateDirection < 0)
	{
		Rotation.Yaw -= QuickRotationAngle;
		Controller->SetControlRotation(Rotation);
	}
	else if(QuickRotateDirection > 0)
	{
		Rotation.Yaw += QuickRotationAngle;
		Controller->SetControlRotation(Rotation);
	}
}


