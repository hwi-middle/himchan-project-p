// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterPlayer.h"
#include "Engine/DamageEvents.h"
#include "Engine/PostProcessVolume.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPCharacterPlayer::APPCharacterPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerStatusData = FPPConstructorHelper::FindAndGetObject<UPPPlayerStatusData>(TEXT("/Script/ProjectP.PPPlayerStatusData'/Game/DataAssets/Player/PlayerStatusData.PlayerStatusData'"), EAssertionLevel::Check);
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollsionCapsule"));
	CollisionCapsule->InitCapsuleSize(15.0f, 90.0f);
	CollisionCapsule->SetCollisionProfileName(TEXT("Pawn"));
	TObjectPtr<USceneComponent> OriginalRootComponent = RootComponent;
	RootComponent = CollisionCapsule;
	OriginalRootComponent->SetupAttachment(RootComponent);
}

void APPCharacterPlayer::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupCharacterStatusData(PlayerStatusData);

	DamageFXFadeInDuration = PlayerStatusData->DamageFXFadeInDuration;
	DamageFXFadeOutDuration = PlayerStatusData->DamageFXFadeOutDuration;

	if (GetWorld()->PostProcessVolumes.IsEmpty())
	{
		return;
	}

	APostProcessVolume* PostProcessVolume = Cast<APostProcessVolume>(GetWorld()->PostProcessVolumes[0]);
	FPostProcessSettings Settings = PostProcessVolume->Settings;

	UMaterial* CustomPostProcessMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/Project-P/Material/PostProcess/PPTest.PPTest'"));
	UMaterialInstanceDynamic* MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(CustomPostProcessMaterial, nullptr);

	Settings.WeightedBlendables.Array.Empty();
	Settings.WeightedBlendables.Array.Add(FWeightedBlendable(1.0f, MaterialInstanceDynamic));
	PostProcessVolume->Settings = Settings;
	DynamicMaterialInstance = MaterialInstanceDynamic;
}

void APPCharacterPlayer::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(HitCheckTimer);
	GetWorldTimerManager().ClearTimer(RecoveryTickTimer);
	GetWorldTimerManager().ClearTimer(DamageFXFadeTimer);
	HitCheckTimer.Invalidate();
	RecoveryTickTimer.Invalidate();
	DamageFXFadeTimer.Invalidate();
}

float APPCharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// TODO: ECharacterState 걷어내기
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageAmount;
	UE_LOG(LogTemp, Log, TEXT("%f만큼의 피해를 입음"), DamageAmount);
	if (Health <= 0)
	{
		CurrentState = ECharacterState::Dead;
		return DamageAmount;
	}

	if (CurrentState == ECharacterState::Idle)
	{
		GetWorldTimerManager().ClearTimer(RecoveryTickTimer);
		CurrentState = ECharacterState::Hit;

		GetWorldTimerManager().SetTimer(HitCheckTimer, FTimerDelegate::CreateLambda([&]()
		{
			//SetCharacterState(ECharacterState::Idle);
			GetWorldTimerManager().ClearTimer(HitCheckTimer);
			EnableRecoveryHealthTimer();
		}), ReturnToIdleStateTime, false);
	}
	else
	{
		if (GetWorldTimerManager().IsTimerActive(HitCheckTimer))
		{
			GetWorldTimerManager().ClearTimer(HitCheckTimer);
		}
	}

	ShowDamageFX();

	return DamageAmount;
}

void APPCharacterPlayer::SetupCharacterStatusData(UDataAsset* CharacterStatusData)
{
	// CharacterStatusData를 기반으로 PlayerCharacter 초기 상태 셋업
	UPPPlayerStatusData* PlayerData = Cast<UPPPlayerStatusData>(CharacterStatusData);
	Health = PlayerData->MaximumHealth;
	RecoveryHealthAmountOnIdle = PlayerData->RecoveryHealthValueOnIdle;
	RecoveryHealthTick = PlayerData->RecoveryHealthTick;
	ReturnToIdleStateTime = PlayerData->ReturnToIdleStateTime;
	CurrentState = ECharacterState::Idle;
}

void APPCharacterPlayer::IncreaseHealth(const float Value)
{
	Health += Value;
}

void APPCharacterPlayer::DecreaseHealth(const float Value)
{
	Health -= Value;
}

void APPCharacterPlayer::EnableRecoveryHealthTimer()
{
	// Idle 상태 자연 회복 관련
	if (Health < PlayerStatusData->MaximumHealth)
	{
		GetWorldTimerManager().SetTimer(RecoveryTickTimer, FTimerDelegate::CreateLambda([&]()
		{
			Health += RecoveryHealthAmountOnIdle;
			if (Health >= PlayerStatusData->MaximumHealth)
			{
				Health = PlayerStatusData->MaximumHealth;
				GetWorldTimerManager().ClearTimer(RecoveryTickTimer);
			}
		}), RecoveryHealthTick, true);
	}
}

void APPCharacterPlayer::ShowDamageFX()
{
	DamageFXIntensity = 0.f;
	ElapsedDamageFXFadeTime = 0.f;
	GetWorldTimerManager().ClearTimer(DamageFXFadeTimer);
	GetWorldTimerManager().SetTimer(DamageFXFadeTimer, FTimerDelegate::CreateLambda([&]()
	{
		float CurrentIntensity;
		// 페이드 인
		if (ElapsedDamageFXFadeTime <= DamageFXFadeInDuration)
		{
			CurrentIntensity = ElapsedDamageFXFadeTime / DamageFXFadeInDuration;
		}
		// 페이드 아웃
		else
		{
			CurrentIntensity = 1 - (ElapsedDamageFXFadeTime - DamageFXFadeInDuration) / DamageFXFadeOutDuration;
		}
		DynamicMaterialInstance->SetScalarParameterValue("Intensity", CurrentIntensity);
		ElapsedDamageFXFadeTime += GetWorld()->DeltaTimeSeconds;

		if (ElapsedDamageFXFadeTime >= DamageFXFadeInDuration + DamageFXFadeOutDuration)
		{
			DynamicMaterialInstance->SetScalarParameterValue("Intensity", 0.f);
			GetWorldTimerManager().ClearTimer(DamageFXFadeTimer);
		}
	}), 0.01f, true);
}
