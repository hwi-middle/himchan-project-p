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
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Prop/Weapon/PPGunBase.h"
#include "ProjectP/UI/Pause/PPPauseWidgetActor.h"
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
	LeftYButtonPressAction = MovementData->LeftYButtonPressAction;
	RightAButtonPressAction = MovementData->RightAButtonPressAction;
	RightBButtonPressAction = MovementData->RightBButtonPressAction;
	
	MoveSpeed = MovementData->WalkSpeed;
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
	
	TArray<AActor*> PauseWidgets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APPPauseWidgetActor::StaticClass(), PauseWidgets);
	if(PauseWidgets.Num() > 0)
	{
		PauseWidget = CastChecked<APPPauseWidgetActor>(PauseWidgets[0]);
	}
	
	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPVRPawn::ClearAllTimerOnLevelChange);
	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	WalkSoundCueArray = SoundData->PlayerWalkTypeASoundCueArray;
	if(WalkSoundCueArray.IsEmpty())
	{
		// 배열이 비어있을 때 크래시 방지용.
		USoundCue* TempSoundCue = nullptr;
		WalkSoundCueArray.Emplace(TempSoundCue);
	}
	WalkSoundRate = SoundData->WalkSoundRate;
	SprintSoundRate = SoundData->SprintSoundRate;
}

void APPVRPawn::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(MoveSoundTimerHandle);
	MoveSoundTimerHandle.Invalidate();
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
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APPVRPawn::StartMove);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APPVRPawn::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APPVRPawn::CompleteMove);
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
	
	EnhancedInputComponent->BindAction(LeftYButtonPressAction, ETriggerEvent::Started, this, &APPVRPawn::PressYButtonAction);
	EnhancedInputComponent->BindAction(LeftXButtonPressAction, ETriggerEvent::Started, this, &APPVRPawn::PressXButtonAction);
	EnhancedInputComponent->BindAction(RightBButtonPressAction, ETriggerEvent::Started, this, &APPVRPawn::PressBButtonAction);
	EnhancedInputComponent->BindAction(RightAButtonPressAction, ETriggerEvent::Started, this, &APPVRPawn::PressAButtonAction);
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
	if(UGameplayStatics::GetGlobalTimeDilation(GetWorld()) != 1.0f)
	{
		return;
	}
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

	if(UGameplayStatics::IsGamePaused(GetWorld()))
	{
		return;
	}
	
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

	if(UGameplayStatics::IsGamePaused(GetWorld()))
	{
		return;
	}
	
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
	
	if(UGameplayStatics::IsGamePaused(GetWorld()))
	{
		return;
	}
	
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

	if(UGameplayStatics::IsGamePaused(GetWorld()))
	{
		return;
	}
	
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

	if(UGameplayStatics::IsGamePaused(GetWorld()))
	{
		return;
	}
	
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

	if(UGameplayStatics::IsGamePaused(GetWorld()))
	{
		return;
	}
	
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

void APPVRPawn::StartMove(const FInputActionValue& Value)
{
	if(GetWorldTimerManager().IsTimerActive(MoveSoundTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(MoveSoundTimerHandle);
	}
	GetWorldTimerManager().SetTimer(MoveSoundTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		WalkSoundCue = WalkSoundCueArray[FMath::RandRange(0, WalkSoundCueArray.Num() - 1)];
		UGameplayStatics::PlaySound2D(this, WalkSoundCue);
	}), WalkSoundRate, true);
}

void APPVRPawn::CompleteMove(const FInputActionValue& Value)
{
	if(GetWorldTimerManager().IsTimerActive(MoveSoundTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(MoveSoundTimerHandle);
	}
	
	if (MoveSpeed == MovementData->SprintSpeed)
	{
		MoveSpeed = MovementData->WalkSpeed;
	}
}

void APPVRPawn::ToggleSprint(const FInputActionValue& Value)
{
	MoveSpeed == MovementData->WalkSpeed ? MoveSpeed = MovementData->SprintSpeed : MoveSpeed = MovementData->WalkSpeed;
	
	if(GetWorldTimerManager().IsTimerActive(MoveSoundTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(MoveSoundTimerHandle);
	}
	if(MoveSpeed == MovementData->WalkSpeed)
	{
		GetWorldTimerManager().SetTimer(MoveSoundTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			WalkSoundCue = WalkSoundCueArray[FMath::RandRange(0, WalkSoundCueArray.Num() - 1)];
			UGameplayStatics::PlaySound2D(this, WalkSoundCue);
		}), WalkSoundRate, true);
	}
	else
	{
		GetWorldTimerManager().SetTimer(MoveSoundTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			WalkSoundCue = WalkSoundCueArray[FMath::RandRange(0, WalkSoundCueArray.Num() - 1)];
			UGameplayStatics::PlaySound2D(this, WalkSoundCue);
		}), SprintSoundRate, true);
	}
}

void APPVRPawn::PressAButtonAction(const FInputActionValue& Value)
{
	if(bIsRightHandMainly)
	{
		ToggleFlash();
	}
	else
	{
		ToggleWidgetInteraction();
	}
}

void APPVRPawn::PressBButtonAction(const FInputActionValue& Value)
{
	if(bIsRightHandMainly)
	{
		// 매핑된게 없서요
	}
	else
	{
		ToggleGamePauseState();
	}
}

void APPVRPawn::PressXButtonAction(const FInputActionValue& Value)
{
	if(bIsRightHandMainly)
	{
		ToggleWidgetInteraction();
	}
	else
	{
		ToggleFlash();
	}
}


void APPVRPawn::PressYButtonAction(const FInputActionValue& Value)
{
	if(bIsRightHandMainly)
	{
		ToggleGamePauseState();
	}
	else
	{
		// 매핑된게 없서요
	}
}

void APPVRPawn::ToggleWidgetInteraction() const
{
	if(bIsRightHandMainly)
	{
		LeftHand->WidgetInteractionToggle(WidgetInteractionDistance);
	}
	else
	{
		RightHand->WidgetInteractionToggle(WidgetInteractionDistance);
	}
}

void APPVRPawn::ToggleGamePauseState() const
{
	if(UGameplayStatics::GetGlobalTimeDilation(GetWorld()) == 1.0f)
	{
		PauseWidget->SetActorRotation(this->GetActorForwardVector().Rotation());
		PauseWidget->SetActorLocation(this->GetActorLocation() + this->GetActorForwardVector() * 200 + PauseWidgetCustomPosition);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.000001f);
	}
	else // TestOnly
	{
		PauseWidget->SetActorLocation(PauseWidget->GetActorLocation() + FVector(0.0f, 0.0f, -10000.0f));
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	}
}

void APPVRPawn::ToggleFlash() const
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

void APPVRPawn::SwapWidgetInteraction() const
{
	if(bIsRightHandMainly)
	{
		LeftHand->SetupWidgetComponent(WidgetInteractionDistance);
		RightHand->DisableWidgetComponent();
	}
	else
	{
		LeftHand->DisableWidgetComponent();
		RightHand->SetupWidgetComponent(WidgetInteractionDistance);
	}
}
