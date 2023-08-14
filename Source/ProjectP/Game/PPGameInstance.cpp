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
	SoundCueLibrary = FPPConstructorHelper::FindAndGetObject<UObjectLibrary>(TEXT("/Script/Engine.ObjectLibrary'/Game/Project-P/DataTable/SoundObjectLibrary.SoundObjectLibrary'"), EAssertionLevel::Check);
}

FStringDataTable* UPPGameInstance::GetStringDataTable(FName RowName)
{
	return StringDataTable->FindRow<FStringDataTable>(RowName, TEXT("Find StringDataTable"));
}
