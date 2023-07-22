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
	CollisionCapsule->InitCapsuleSize(45.0f,90.0f);
	CollisionCapsule->SetCollisionProfileName(TEXT("Pawn"));
	TObjectPtr<USceneComponent> BeforeRootComponent = RootComponent;
	RootComponent = CollisionCapsule;
	BeforeRootComponent->SetupAttachment(RootComponent);
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

float APPCharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
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
		CurrentState = ECharacterState::Hit;
		if(GetWorldTimerManager().IsTimerActive(HitCheckTimer))
		{
			GetWorldTimerManager().ClearTimer(HitCheckTimer);
		}
		if(GetWorldTimerManager().IsTimerActive(RecoveryTickTimer))
		{
			GetWorldTimerManager().ClearTimer(RecoveryTickTimer);
		}
		GetWorldTimerManager().SetTimer(HitCheckTimer, this, &APPCharacterPlayer::ReturnIdleState, ReturnToIdleStateTime, false);
	}
	return DamageAmount;
}

void APPCharacterPlayer::SetupCharacterStatusData(UDataAsset* CharacterStatusData)
{
	// CharacterStatusData를 기반으로 PlayerCharacter 초기 상태 셋업
	UPPPlayerStatusData* PlayerData = Cast<UPPPlayerStatusData>(CharacterStatusData);
	Health = PlayerData->DefaultHealth;
	RecoveryHealthValueOnIdle = PlayerData->RecoveryHealthValueOnIdle;
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

void APPCharacterPlayer::ReturnIdleState()
{
	SetCharacterState(ECharacterState::Idle);
	// 만약 상태가 다양해진다면 인자로 현재 상태를 받아서 switch문 돌리는 방식으로 변경
	GetWorldTimerManager().ClearTimer(HitCheckTimer);
	
	if(Health != PlayerStatusData->DefaultHealth)
	{
		GetWorldTimerManager().SetTimer(HitCheckTimer, FTimerDelegate::CreateLambda([&]()
		{
			IncreaseHealth(RecoveryHealthValueOnIdle);
		}), 1.0f, false);
	}
}




