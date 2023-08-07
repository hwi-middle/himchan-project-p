// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Prop/Weapon/PPGunBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Grab/PPVRGrabComponent.h"
#include "ProjectP/Player/PPVRHand.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPGunBase::APPGunBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	// TODO: Socket으로 분리
	MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePosition"));
	MuzzlePosition->SetupAttachment(WeaponMesh);

	LaserPosition = CreateDefaultSubobject<USceneComponent>(TEXT("LaserPosition"));
	LaserPosition->SetupAttachment(WeaponMesh);

	FlashPosition = CreateDefaultSubobject<USceneComponent>(TEXT("FlashPosition"));
	FlashPosition->SetupAttachment(WeaponMesh);

	GripPosition = CreateDefaultSubobject<USceneComponent>(TEXT("GripPosition"));
	GripPosition->SetupAttachment(WeaponMesh);

	GrabComponent = CreateDefaultSubobject<UPPVRGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(WeaponMesh);
	GrabComponent->SetRelativeLocation(GripPosition->GetRelativeLocation());

	LeftShootAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/Weapon/IA_VRShootLeft.IA_VRShootLeft'"), EAssertionLevel::Check);
	RightShootAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/Weapon/IA_VRShootRight.IA_VRShootRight'"), EAssertionLevel::Check);
	LeftHandInputMappingContext = FPPConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/15-Basic-Movement/Input/IMC_Weapon_Left.IMC_Weapon_Left'"), EAssertionLevel::Check);
	RightHandInputMappingContext = FPPConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/15-Basic-Movement/Input/IMC_Weapon_Right.IMC_Weapon_Right'"), EAssertionLevel::Check);
}

void APPGunBase::BeginPlay()
{
	Super::BeginPlay();
	UPPVRGrabComponent* GrabComponentCasted = Cast<UPPVRGrabComponent>(GrabComponent);
	GrabComponentCasted->OnGrab.AddUObject(this, &APPGunBase::GrabOnHand);
	GrabComponentCasted->OnRelease.AddUObject(this, &APPGunBase::ReleaseOnHand);
}

void APPGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float Distance = 1000.f;
	FVector StartLocation = MuzzlePosition->GetComponentLocation();
	FVector ForwardVector = MuzzlePosition->GetForwardVector();
	FVector EndLocation = StartLocation + ForwardVector * Distance;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		CollisionParams
	);

	if (bHit)
	{
		AimingActor = HitResult.GetActor();
		if (AimingActor)
		{
			FString HitActorName = AimingActor->GetName();
			FVector HitLocation = HitResult.ImpactPoint;
			// UE_LOG(LogTemp, Warning, TEXT("Hit %s at location %s"), *HitActorName, *HitLocation.ToString());
		}
		DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Red, false, 0.03f, 0, 1.0f);
	}
	else
	{
		AimingActor = nullptr;
		// UE_LOG(LogTemp, Warning, TEXT("Nothing hit along the raycast path"));
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0.03f, 0, 1.0f);
	}
}

void APPGunBase::SetupWeaponData(UPPWeaponData* WeaponData)
{
	NormalShotDamageMin = WeaponData->NormalShotDamageMin;
	WeaponMesh->SetSkeletalMesh(WeaponData->WeaponMesh);
}

void APPGunBase::PressTrigger()
{
	/*
	 * Called to Player InputAction
	 * Check Ammo remain
	 * If Ammo is left, Call OnFire every BaseWeaponShootRate seconds
	 * Change weapon's state to Fire
	 */
}

void APPGunBase::OnFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Hit %s at location %s"), *AimingActor->GetName(), *AimingActor->GetActorLocation().ToString());
}

void APPGunBase::GrabOnHand(APPVRHand* InHand)
{
	UE_LOG(LogTemp, Log, TEXT("OnGrab"));
	//SetupInputMappingContextByHandType(InHand->GetHandType());
}

void APPGunBase::ReleaseOnHand(APPVRHand* InHand)
{

}

void APPGunBase::ToggleLaserPoint()
{
	if (!bIsLaserPointEnable)
	{
		/*
		 * Do something
		 */
		bIsLaserPointEnable = true;
	}
	else
	{
		/*
		 * Do something
		 */
		bIsLaserPointEnable = false;
	}
}

void APPGunBase::SetupInputMappingContextByHandType(const EControllerHand InHandType)
{
	const UInputMappingContext* FinalInputMappingContext = nullptr;
	const UInputAction* FinalInputAction = nullptr;

	switch (InHandType)
	{
	case EControllerHand::Left:
		FinalInputMappingContext = LeftHandInputMappingContext;
		FinalInputAction = LeftShootAction;
		break;
	case EControllerHand::Right:
		FinalInputMappingContext = RightHandInputMappingContext;
		FinalInputAction = RightShootAction;
		break;
	default:
		checkNoEntry();
	}

	// EnableInput(PlayerController);
	// PlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	// PlayerSubSystem->AddMappingContext(FinalInputMappingContext, 10);
	//
	// UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->GetComponentByClass(UEnhancedInputComponent::StaticClass()));
	// EnhancedInputComponent->BindAction(FinalInputAction, ETriggerEvent::Started, this, &APPGunBase::OnFire);
	//
	// check(PlayerController->GetLocalPlayer());
	// check(PlayerSubSystem);
	// check(FinalInputAction);
	// check(FinalInputMappingContext);
}

void APPGunBase::ToggleFlashlight()
{
	if (!bIsFlashlightEnable)
	{
		/*
		 * Do something
		 */
		bIsFlashlightEnable = true;
	}
	else
	{
		/*
		 * Do something
		 */
		bIsFlashlightEnable = false;
	}
}
