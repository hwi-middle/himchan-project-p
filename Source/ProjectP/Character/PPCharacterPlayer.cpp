// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectP/Character/PPCharacterPlayer.h"

// Sets default values
APPCharacterPlayer::APPCharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

void APPCharacterPlayer::SetupCharacterStatusData(const UPPCharacterStatusData* CharacterStatusData)
{
	// CharacterStatusData를 기반으로 PlayerCharacter 초기 상태 셋업
}

void APPCharacterPlayer::SetIdleState()
{
	PlayerCurrentState = Idle;
}

void APPCharacterPlayer::SetDeadState()
{
	PlayerCurrentState = Dead;
}

const float APPCharacterPlayer::GetCurrentHealth()
{
	return PlayerHealth;
}

void APPCharacterPlayer::RecoveryHealth(const float Health)
{
	PlayerHealth += Health;
}

const uint8 APPCharacterPlayer::GetCurrentState()
{
	return PlayerCurrentState;
}



