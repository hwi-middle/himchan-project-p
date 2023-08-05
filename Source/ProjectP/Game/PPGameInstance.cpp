// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Game/PPGameInstance.h"
#include "Kismet/GameplayStatics.h"

UPPGameInstance::UPPGameInstance()
{
	SaveSettingOption = CastChecked<UPPSaveSettingOption>(UGameplayStatics::CreateSaveGameObject(UPPSaveSettingOption::StaticClass()));
	SaveSettingOption = CastChecked<UPPSaveSettingOption>(UGameplayStatics::LoadGameFromSlot(SaveSettingOption->SaveFileName, 0));
}
