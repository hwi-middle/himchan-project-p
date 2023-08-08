// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Game/PPGameInstance.h"
#include "Kismet/GameplayStatics.h"

UPPGameInstance::UPPGameInstance()
{
	SaveSettingOption = CastChecked<UPPSaveSettingOption>(UGameplayStatics::CreateSaveGameObject(UPPSaveSettingOption::StaticClass()));
	TObjectPtr<UPPSaveSettingOption> SavedOption= Cast<UPPSaveSettingOption>(UGameplayStatics::LoadGameFromSlot(SaveSettingOption->SaveFileName, 0));
	if(SavedOption)
	{
		SaveSettingOption = SavedOption;
	}
}
