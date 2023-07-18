// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterBoss.h"

APPCharacterBoss::APPCharacterBoss()
{
	
}

void APPCharacterBoss::SetupCharacterStatusData(const UPPCharacterStatusData* CharacterStatusData)
{
	
}

void APPCharacterBoss::IncreaseHealth(const float Value)
{
	Health += Value;
}

void APPCharacterBoss::DecreaseHealth(const float Value)
{
	Health -= Value;
}
