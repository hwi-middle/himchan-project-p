// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Prop/Weapon/PPGunBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputCoreTypes.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Grab/PPVRGrabComponent.h"
#include "ProjectP/Player/PPVRHand.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "Math/UnrealMathUtility.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Object/PPDestructible.h"
#include "ProjectP/Util/PPDrawLineHelper.h"
#include "ProjectP/Util/PPTimerHelper.h"

// Sets default values
APPGunBase::APPGunBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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
	UNiagaraSystem* MuzzleNiagaraSystem = FPPConstructorHelper::FindAndGetObject<UNiagaraSystem>(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX_SciFi_Muzzle_And_Impact_Pack_1/VFX/Presets/Muzzle/NE_VFX_Muzzle_Physical_Burst_1.NE_VFX_Muzzle_Physical_Burst_1'"), EAssertionLevel::Check);
	MuzzleNiagaraEffect->SetAsset(MuzzleNiagaraSystem);
	MuzzleNiagaraEffect->SetAutoActivate(false);
	MuzzleNiagaraEffect->SetActive(false);

	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetIntensityUnits(ELightUnits::Candelas);
	Flashlight->SetupAttachment(WeaponMesh);
	// Flashlight->SetVisibility(false);

	GrabComponent = CreateDefaultSubobject<UPPVRGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(WeaponMesh);

	LeftShootAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/Weapon/IA_VRShootLeft.IA_VRShootLeft'"), EAssertionLevel::Check);
	RightShootAction = FPPConstructorHelper::FindAndGetObject<UInputAction>(TEXT("/Script/EnhancedInput.InputAction'/Game/15-Basic-Movement/Input/InputAction/Weapon/IA_VRShootRight.IA_VRShootRight'"), EAssertionLevel::Check);
	LeftHandInputMappingContext = FPPConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/15-Basic-Movement/Input/IMC_Weapon_Left.IMC_Weapon_Left'"), EAssertionLevel::Check);
	RightHandInputMappingContext = FPPConstructorHelper::FindAndGetObject<UInputMappingContext>(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/15-Basic-Movement/Input/IMC_Weapon_Right.IMC_Weapon_Right'"), EAssertionLevel::Check);

	bIsOnShooting = false;
	bIsFlashlightEnable = false;
	bIsCooldownStart = false;
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
	// GrabComponent->SetRelativeLocation(WeaponMesh->GetSocketTransform(GUN_GRIP, ERelativeTransformSpace::RTS_Actor).GetLocation());
	MuzzleNiagaraEffect->SetActive(false);

	Flashlight->SetWorldLocation(WeaponMesh->GetSocketLocation(GUN_FLASH));
	Flashlight->SetWorldRotation(WeaponMesh->GetSocketRotation(GUN_FLASH));

	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPGunBase::ClearAllTimerOnLevelChange);

	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	FireSoundCueArray = SoundData->GunOnFireSoundCueArray;
	if (FireSoundCueArray.IsEmpty())
	{
		// 배열이 비어있을 때 크래시 방지용.
		USoundCue* TempSoundCue = nullptr;
		FireSoundCueArray.Emplace(TempSoundCue);
	}
	GrabOnHandSoundCue = SoundData->GunGrabOnHandSoundCue;
	CoolDownSoundCue = SoundData->GunCoolDownSoundCue;
	IncreaseOverheatSoundCue = SoundData->IncreaseGunOverheatGaugeSoundCue;
	OverheatGaugeMaxSoundCue = SoundData->GunOverheatGaugeMaxSoundCue;
	ToggleFlashSoundCue = SoundData->GunToggleFlashSoundCue;
}

void APPGunBase::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(BlockShootTimerHandle);
	GetWorldTimerManager().ClearTimer(OverheatCoolDownTimerHandle);
	BlockShootTimerHandle.Invalidate();
	OverheatCoolDownTimerHandle.Invalidate();
}

void APPGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WeaponMesh->SetScalarParameterValueOnMaterials(TEXT("Alpha"), CurrentOverheat / MaxOverheat);

	if (!bHeld)
	{
		return;
	}

	MuzzleNiagaraEffect->SetRelativeLocation(WeaponMesh->GetSocketLocation(GUN_MUZZLE_FOR_FX));
	MuzzleNiagaraEffect->SetRelativeRotation(WeaponMesh->GetSocketRotation(GUN_MUZZLE_FOR_FX));

	float Distance = 1000.f;
	FVector StartLocation = WeaponMesh->GetSocketLocation(GUN_MUZZLE_FOR_AIMING);
	FVector ForwardVector = WeaponMesh->GetSocketTransform(GUN_MUZZLE_FOR_AIMING).GetUnitAxis(EAxis::X);
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
		FPPDrawLineHelper::DrawLine(GetWorld(), StartLocation, EndLocation, LineColor, false, -1, 0, 1.0f);
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
	FPPDrawLineHelper::DrawLine(GetWorld(), StartLocation, HitResult.ImpactPoint, LineColor, false, -1, 0, 1.0f);

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
	CooldownDelay = WeaponData->CooldownDelay;
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
	// 과열 게이지 쿨다운 타이머 삭제
	GetWorldTimerManager().ClearTimer(OverheatCoolDownTimerHandle);

	const float DeltaTime = GetWorld()->DeltaTimeSeconds;
	ElapsedTimeAfterLastShoot += DeltaTime;

	// 발사 주기가 되지 않았다면 return
	if (ElapsedTimeAfterLastShoot < ShootDelayPerShoot)
	{
		return;
	}

	// 발사 주기 카운트 초기화
	ElapsedTimeAfterLastShoot = 0.f;

	// 발사 주기가 되긴 했는데 발사가 불가능한 상태면 return
	if (bIsUnavailable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unavailable!"));
		return;
	}

	// 발사 이펙트 적용
	bIsOnShooting = true;
	bIsCooldownStart = false;
	MuzzleNiagaraEffect->SetActive(true);
    MuzzleNiagaraEffect->Deactivate();
    MuzzleNiagaraEffect->Activate();
    
	OnFireSoundCue = FireSoundCueArray[FMath::RandRange(0, FireSoundCueArray.Num() - 1)];
	UGameplayStatics::PlaySound2D(this, OnFireSoundCue);
	UGameplayStatics::PlaySound2D(this, IncreaseOverheatSoundCue);

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
		else if (UPPDestructible* Component = AimingActor->FindComponentByClass<UPPDestructible>())
		{
			const float Damage = FMath::RandRange(NormalShotDamageMin, NormalShotDamageMax);
			Component->DecreaseHealth(Damage);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Nowhere"));
	}

	// 과열상태 처리
	if (CurrentOverheat >= MaxOverheat)
	{
		UGameplayStatics::PlaySound2D(this, OverheatGaugeMaxSoundCue);
		bIsUnavailable = true;
		LineColor = FColor::Red;
		MuzzleNiagaraEffect->SetActive(false);

		ElapsedUnavailableTime = 0.f;
		if (CrossHairPlane->GetStaticMesh() != OverheatedCrossHair)
		{
			CrossHairPlane->SetStaticMesh(OverheatedCrossHair);
		}

		GetWorldTimerManager().SetTimer(BlockShootTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			GetWorldTimerManager().ClearTimer(OverheatCoolDownTimerHandle);

			CurrentOverheat = FMath::Lerp(MaxOverheat, 0.f, ElapsedUnavailableTime / UnavailableTime);

			if (ElapsedUnavailableTime >= UnavailableTime)
			{
				bIsUnavailable = false;
				LineColor = FColor::Green;
				CurrentOverheat = 0.f;
				CrossHairPlane->SetStaticMesh(DefaultCrossHair);
				GetWorldTimerManager().ClearTimer(BlockShootTimerHandle);
				FPPTimerHelper::InvalidateTimerHandle(BlockShootTimerHandle);
				return;
			}
			ElapsedUnavailableTime += FPPTimerHelper::GetActualDeltaTime(BlockShootTimerHandle);
		}), 0.01f, true);
	}
}

void APPGunBase::StopFire()
{
	bIsOnShooting = false;
	MuzzleNiagaraEffect->SetActive(false);
	ElapsedTimeAfterLastShoot = ShootDelayPerShoot;

	// 정지 후 CooldownDelay 만큼의 시간이 흐르면 Cooldown 시작
	GetWorldTimerManager().SetTimer(OverheatCoolDownTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		if (!FPPTimerHelper::IsDelayElapsed(OverheatCoolDownTimerHandle, CooldownDelay))
		{
			return;
		}

		if (!bIsCooldownStart)
		{
			bIsCooldownStart = true;
			UGameplayStatics::PlaySound2D(this, CoolDownSoundCue);
		}

		const float DeltaTime = FPPTimerHelper::GetActualDeltaTime(OverheatCoolDownTimerHandle);
		CurrentOverheat -= OverheatCoolDownPerSecond * DeltaTime;
		UE_LOG(LogTemp, Log, TEXT("Cooldowned: %f"), CurrentOverheat);
		if (CurrentOverheat < KINDA_SMALL_NUMBER)
		{
			UE_LOG(LogTemp, Log, TEXT("No more overheat now"));
			bIsCooldownStart = false;
			CurrentOverheat = 0.f;
			GetWorldTimerManager().ClearTimer(OverheatCoolDownTimerHandle);
			FPPTimerHelper::InvalidateTimerHandle(BlockShootTimerHandle);
		}
	}), 0.01f, true);

}

void APPGunBase::GrabOnHand(APPVRHand* InHand)
{
	UGameplayStatics::PlaySound2D(this, GrabOnHandSoundCue);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bHeld = true;

	//UE_LOG(LogTemp, Log, TEXT("OnGrab"));
	//SetupInputMappingContextByHandType(InHand->GetHandType());
}

void APPGunBase::ReleaseOnHand(APPVRHand* InHand)
{
	CrossHairPlane->SetVisibility(false);
	MuzzleNiagaraEffect->SetActive(false);
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
	UGameplayStatics::PlaySound2D(this, ToggleFlashSoundCue);
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
