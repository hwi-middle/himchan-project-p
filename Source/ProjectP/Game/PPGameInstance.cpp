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
	
	TObjectPtr<UObjectLibrary> SoundCueLibrary = FPPConstructorHelper::FindAndGetObject<UObjectLibrary>(TEXT("/Script/Engine.ObjectLibrary'/Game/Project-P/DataTable/SoundObjectLibrary.SoundObjectLibrary'"), EAssertionLevel::Check);
	if(SoundCueLibrary)
	{
		TArray<USoundCue*> SoundCueTempArray;
		SoundCueLibrary->GetObjects(SoundCueTempArray);
		for (auto SoundCue : SoundCueTempArray)
		{
			FString SoundCueName = SoundCue->GetName();
			SoundCueMap.Emplace(SoundCueName, SoundCue);
			UE_LOG(LogTemp, Log, TEXT("Add SoundCueName: %s"), *SoundCueName);
		}
	}
}

FStringDataTable* UPPGameInstance::GetStringDataTable(const FName RowName)
{
	return StringDataTable->FindRow<FStringDataTable>(RowName, TEXT("Find StringDataTable"));
}

TObjectPtr<USoundCue> UPPGameInstance::GetSoundCue(const FString SoundName)
{
	//check(SoundCueMap.Contains(SoundName));
	if(SoundCueMap.Contains(SoundName))
	{
		return SoundCueMap[SoundName];
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Access invalid SoundKey by %s"), *SoundName);
		return nullptr;
	}
}
