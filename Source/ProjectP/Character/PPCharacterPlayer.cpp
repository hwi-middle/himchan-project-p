// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterPlayer.h"
#include "Engine/DamageEvents.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPCharacterPlayer::APPCharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerStatusData = FPPConstructorHelper::FindAndGetObject<UPPPlayerStatusData>(TEXT("/Script/ProjectP.PPPlayerStatusData'/Game/DataAssets/Player/PlayerStatusData.PlayerStatusData'"), EAssertionLevel::Check);
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollsionCapsule"));
	CollisionCapsule->InitCapsuleSize(5.0f,90.0f);
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
}

float APPCharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageAmount;
	if(Health <= 0)
	{
		CurrentState = ECharacterState::Dead;
		return DamageAmount;
	}
	
	if(CurrentState == ECharacterState::Idle)
	{
		GetWorldTimerManager().ClearTimer(RecoveryTickTimer);
		CurrentState = ECharacterState::Hit;
		
		GetWorldTimerManager().SetTimer(HitCheckTimer, FTimerDelegate::CreateLambda([&]()
		{
			SetCharacterState(ECharacterState::Idle);
			GetWorldTimerManager().ClearTimer(HitCheckTimer);
			EnableRecoveryHealthTimer();
		}), ReturnToIdleStateTime, false);
	}
	else
	{
		if(GetWorldTimerManager().IsTimerActive(HitCheckTimer))
		{
			GetWorldTimerManager().ClearTimer(HitCheckTimer);
		}
	}
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
	if(Health < PlayerStatusData->MaximumHealth)
	{
		GetWorldTimerManager().SetTimer(RecoveryTickTimer, FTimerDelegate::CreateLambda([&]()
		{
			Health += RecoveryHealthAmountOnIdle;
			if(Health >= PlayerStatusData->MaximumHealth)
			{
				Health = PlayerStatusData->MaximumHealth;
				GetWorldTimerManager().ClearTimer(RecoveryTickTimer);
			}
		}), RecoveryHealthTick, true);
	}
}





