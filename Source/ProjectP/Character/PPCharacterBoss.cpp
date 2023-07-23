// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterBoss.h"

#include "ProjectP/AI/Boss/PPBossAIController.h"

APPCharacterBoss::APPCharacterBoss()
{
	AIControllerClass = APPBossAIController::StaticClass();
}

void APPCharacterBoss::SetupCharacterStatusData(UDataAsset* CharacterStatusData)
{
	
}

void APPCharacterBoss::IncreaseHealth(const float Value)
{
	/*
	 * Do something
	 */
	Health += Value;
}

void APPCharacterBoss::DecreaseHealth(const float Value)
{
	/*
	 * Do something
	 */
	Health -= Value;
}
