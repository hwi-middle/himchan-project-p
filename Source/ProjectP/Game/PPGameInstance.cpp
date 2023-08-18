// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Game/PPGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Util/PPConstructorHelper.h"

UPPGameInstance::UPPGameInstance()
{
	SaveSettingOption = CastChecked<UPPSaveSettingOption>(UGameplayStatics::CreateSaveGameObject(UPPSaveSettingOption::StaticClass()));
	TObjectPtr<UPPSaveSettingOption> SavedOption= Cast<UPPSaveSettingOption>(UGameplayStatics::LoadGameFromSlot(SaveSettingOption->SaveFileName, 0));
	if(SavedOption)
	{
		SaveSettingOption = SavedOption;
	}
	
	StringDataTable = FPPConstructorHelper::FindAndGetObject<UDataTable>(TEXT("/Script/Engine.DataTable'/Game/Project-P/DataTable/StringData.StringData'"), EAssertionLevel::Check);

	SoundData = FPPConstructorHelper::FindAndGetObject<UPPSoundData>(TEXT("/Script/ProjectP.PPSoundData'/Game/DataAssets/Util/SoundData.SoundData'"), EAssertionLevel::Check);
}

FStringDataTable* UPPGameInstance::GetStringDataTable(const FName RowName)
{
	return StringDataTable->FindRow<FStringDataTable>(RowName, TEXT("Find StringDataTable"));
}
