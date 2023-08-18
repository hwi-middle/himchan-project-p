// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Prop/Weapon/PPGunBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputCoreTypes.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterBase.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "ProjectP/Character/PPCharacterEnemy.h"
#include "ProjectP/Grab/PPVRGrabComponent.h"
#include "ProjectP/Player/PPVRHand.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "Math/UnrealMathUtility.h"
#include "ProjectP/Object/PPDestructible.h"

// Sets default values
APPGunBase::APPGunBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionObjectType(ECC_GIMMICK);

	CrossHairPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrossHairPlane"));
	DefaultCrossHair = FPPConstructorHelper::FindAndGetObject<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Project-P/Meshes/CrossHair/SM_CrossHair.SM_CrossHair'"), EAssertionLevel::Check);
	OverheatedCrossHair = FPPConstructorHelper::FindAndGetObject<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Project-P/Meshes/CrossHair/SM_CrossHair_Detect.SM_CrossHair_Detect'"), EAssertionLevel::Check);
	CrossHairPlane->SetStaticMesh(DefaultCrossHair);
	CrossHairPlane->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CrossHairPlane->SetCollisionObjectType(ECC_WorldStatic);
	CrossHairPlane->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	CrossHairPlane->SetCastShadow(false);
	CrossHairPlane->SetVisibility(false);
	CrossHairPlane->SetupAttachment(WeaponMesh);

	MuzzleNiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleVFX"));
	UNiagaraSystem* MuzzleNiagaraSystem = FPPConstructorHelper::FindAndGetObject<UNiagaraSystem>(TEXT("/Script/Niagara.NiagaraSystem'/Game/Project-P/VFX/GUN_Fire/NS_Flash.NS_Flash'"), EAssertionLevel::Check);
	MuzzleNiagaraEffect->SetAsset(MuzzleNiagaraSystem);
	MuzzleNiagaraEffect->SetActive(false);
	
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetIntensityUnits(ELightUnits::Candelas);
	Flashlight->SetupAttachment(WeaponMesh);
	Flashlight->SetVisibility(false);

	GrabComponent = CreateDefaultSubobject<UPPVRGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(WeaponMesh);

	LeftShootAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/Weapon/IA_VRShootLeft.IA_VRShootLeft'"), EAssertionLevel::Check);
	RightShootAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/Weapon/IA_VRShootRight.IA_VRShootRight'"), EAssertionLevel::Check);
	LeftHandInputMappingContext = FPPConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/15-Basic-Movement/Input/IMC_Weapon_Left.IMC_Weapon_Left'"), EAssertionLevel::Check);
	RightHandInputMappingContext = FPPConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/15-Basic-Movement/Input/IMC_Weapon_Right.IMC_Weapon_Right'"), EAssertionLevel::Check);

	bIsOnShooting = false;
	bIsFlashlightEnable = false;
	bIsUnavailable = false;
	bHeld = false;
	LineColor = FColor::Green;
	CurrentOverheat = 0;
}

void APPGunBase::BeginPlay()
{
	Super::BeginPlay();
	UPPVRGrabComponent* GrabComponentCasted = Cast<UPPVRGrabComponent>(GrabComponent);
	GrabComponentCasted->OnGrab.AddUObject(this, &APPGunBase::GrabOnHand);
	GrabComponentCasted->OnRelease.AddUObject(this, &APPGunBase::ReleaseOnHand);
	GrabComponent->SetRelativeLocation(WeaponMesh->GetSocketLocation(GUN_GRIP));
	MuzzleNiagaraEffect->SetActive(false);
	
	Flashlight->SetWorldLocation(WeaponMesh->GetSocketLocation(GUN_FLASH));
	Flashlight->SetWorldRotation(WeaponMesh->GetSocketRotation(GUN_FLASH));
}

void APPGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bHeld)
	{
		return;
	}

	MuzzleNiagaraEffect->SetRelativeLocation(WeaponMesh->GetSocketLocation(GUN_MUZZLE));
	MuzzleNiagaraEffect->SetRelativeRotation(WeaponMesh->GetSocketRotation(GUN_MUZZLE));
	
	WeaponMesh->SetScalarParameterValueOnMaterials(TEXT("Alpha"), CurrentOverheat / MaxOverheat);
	
	float Distance = 1000.f;
	FVector StartLocation = WeaponMesh->GetSocketLocation(GUN_MUZZLE);
	FVector ForwardVector = WeaponMesh->GetSocketTransform(GUN_MUZZLE).GetUnitAxis(EAxis::X);
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

	if (!bHit)
	{
		AimingActor = nullptr;
		// UE_LOG(LogTemp, Warning, TEXT("Nothing hit along the raycast path"));
		CrossHairPlane->SetVisibility(false);
		// FlushPersistentDebugLines(GetWorld());
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, LineColor, false, -1, 0, 1.0f);
		return;
	}
	
	AimingActor = HitResult.GetActor();

	if (!AimingActor)
	{
		return;
	}
	
	// 테스트용 태그. 나중에 태그 모음집 헤더파일 만들어서 관리하기?
	if (AimingActor->Tags.Contains("DestructibleObject"))
	{
		CrossHairPlane->SetVisibility(true);
	}
	else
	{
		CrossHairPlane->SetVisibility(false);
	}
	// FlushPersistentDebugLines(GetWorld());
	DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, LineColor, false, -1, 0, 1.0f);
	
	FString HitActorName = AimingActor->GetName();
	FVector HitLocation = HitResult.ImpactPoint;
	CrossHairPlane->SetWorldLocation(HitLocation);
	// UE_LOG(LogTemp, Warning, TEXT("Hit %s at location %s"), *HitActorName, *HitLocation.ToString());
}

void APPGunBase::SetupWeaponData(UPPWeaponData* WeaponData)
{
	WeaponMesh->SetSkeletalMesh(WeaponData->WeaponMesh);
	NormalShotDamageMin = WeaponData->NormalShotDamageMin;
	NormalShotDamageMax = WeaponData->NormalShotDamageMax;
	HeadShotDamageMin = WeaponData->HeadShotDamageMin;
	HeadShotDamageMax = WeaponData->HeadShotDamageMax;
	MaxOverheat = WeaponData->MaxOverheat;
	UnavailableTime = WeaponData->UnavailableTime;
	OverheatAmountPerSingleShoot = WeaponData->OverheatAmountPerSingleShoot;
	ShootPerSecond = WeaponData->ShootPerSecond;
	ShootDelayPerShoot = 1.0f / ShootPerSecond;
	OverheatCoolDownPerSecond = WeaponData->OverheatCoolDownPerSecond;
	ElapsedTimeAfterLastShoot = ShootDelayPerShoot; // 첫 발사 시에는 바로 발사부터 되도록
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
	const float DeltaTime = GetWorld()->DeltaTimeSeconds;
	if(!bIsOnShooting)
	{
		bIsOnShooting = true;
		MuzzleNiagaraEffect->SetActive(true);
	}
	// 게이지가 0인 상태에서 발사할 때 부터 게이지 감소가 시작
	if (CurrentOverheat <= KINDA_SMALL_NUMBER)
	{
		GetWorldTimerManager().SetTimer(OverheatCoolDownTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			CurrentOverheat -= OverheatCoolDownPerSecond * 0.01f;
			UE_LOG(LogTemp, Log, TEXT("Cooldowned: %f"), CurrentOverheat);
			if (CurrentOverheat < KINDA_SMALL_NUMBER)
			{
				UE_LOG(LogTemp, Log, TEXT("No more overheat now"));
				CurrentOverheat = 0.f;
				GetWorldTimerManager().ClearTimer(OverheatCoolDownTimerHandle);
			}
		}), 0.01f, true);
	}

	ElapsedTimeAfterLastShoot += DeltaTime;
	if (ElapsedTimeAfterLastShoot >= ShootDelayPerShoot)
	{
		ElapsedTimeAfterLastShoot = 0.f;

		if (bIsUnavailable)
		{
			UE_LOG(LogTemp, Warning, TEXT("Unavailable!"));
			return;
		}

		CurrentOverheat += OverheatAmountPerSingleShoot;

		if (AimingActor)
		{
			if (ICharacterStatusInterface* Enemy = Cast<ICharacterStatusInterface>(AimingActor))
			{
				const float Damage = FMath::RandRange(NormalShotDamageMin, NormalShotDamageMax);
				
				Enemy->DecreaseHealth(Damage);
				UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
				UE_LOG(LogTemp, Warning, TEXT("Hit %s at location %s"), *AimingActor->GetName(), *AimingActor->GetActorLocation().ToString());
			}
			else if(UPPDestructible* Component = AimingActor->FindComponentByClass<UPPDestructible>())
			{
				const float Damage = FMath::RandRange(NormalShotDamageMin, NormalShotDamageMax);
				Component->DecreaseHealth(Damage);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Nowhere"));
		}
	}

	if (CurrentOverheat > MaxOverheat)
	{
		bIsUnavailable = true;
		// TestOnly
		CurrentUnavailableTime = UnavailableTime;
		if (CrossHairPlane->GetStaticMesh() != OverheatedCrossHair)
		{
			CrossHairPlane->SetStaticMesh(OverheatedCrossHair);
		}
		LineColor = FColor::Red;
		
		GetWorldTimerManager().SetTimer(BlockShootTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			CurrentUnavailableTime -= 0.01f;
			if(CurrentUnavailableTime <= 0.0f)
			{
				bIsUnavailable = false;
				LineColor = FColor::Green;
				CrossHairPlane->SetStaticMesh(DefaultCrossHair);
				GetWorldTimerManager().ClearTimer(BlockShootTimerHandle);
			}
		}), 0.01f, true);
		//
		
		/*
		GetWorldTimerManager().SetTimer(BlockShootTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			bIsUnavailable = false;
		}), UnavailableTime, false);
		*/
	}
}

void APPGunBase::StopFire()
{
	bIsOnShooting = false;
	MuzzleNiagaraEffect->SetActive(false);
	ElapsedTimeAfterLastShoot = ShootDelayPerShoot;
}

void APPGunBase::GrabOnHand(APPVRHand* InHand)
{
	CrossHairPlane->SetVisibility(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bHeld = true;

	//UE_LOG(LogTemp, Log, TEXT("OnGrab"));
	//SetupInputMappingContextByHandType(InHand->GetHandType());
}

void APPGunBase::ReleaseOnHand(APPVRHand* InHand)
{
	CrossHairPlane->SetVisibility(false);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bHeld = false;
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

void APPGunBase::ToggleFlash()
{
	if (!bIsFlashlightEnable)
	{
		Flashlight->SetVisibility(true);
		bIsFlashlightEnable = true;
	}
	else
	{

		Flashlight->SetVisibility(false);
		bIsFlashlightEnable = false;
	}
}
