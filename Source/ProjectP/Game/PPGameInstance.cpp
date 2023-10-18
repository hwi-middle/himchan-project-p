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


//커스텀 커맨드
void UPPGameInstance::PP_Boss_Log_HP()
{
	if (BossCharacter == nullptr)
	{
		BossCharacter = Cast<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));
		if (BossCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	message = FString::Printf(TEXT("Boss HP : %f"), BossCharacter->GetCurrentHealth());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Boss_Increase_HP(float value)
{
	if (BossCharacter == nullptr)
	{
		BossCharacter = Cast<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));

		if (BossCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	BossCharacter->IncreaseHealth(value);
	message = FString::Printf(TEXT("Increased Boss HP : %f"), BossCharacter->GetCurrentHealth());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Boss_Decrease_HP(float value)
{
	if (BossCharacter == nullptr)
	{
		BossCharacter = Cast<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));

		if (BossCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	BossCharacter->DecreaseHealth(value);
	message = FString::Printf(TEXT("Decreased Boss HP : %f"), BossCharacter->GetCurrentHealth());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Boss_Gimmick_Leaf()
{
	if (BossCharacter == nullptr)
	{
		BossCharacter = Cast<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));

		if (BossCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	BossCharacter->TestPattern(EBossPattern::LeafTempest);
	message = FString::Printf(TEXT("Boss Pattern : %s"), TEXT("LeafTempest"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Boss_Gimmick_Tentacle()
{
	if (BossCharacter == nullptr)
	{
		BossCharacter = Cast<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));

		if (BossCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	BossCharacter->TestPattern(EBossPattern::VineGarden);
	message = FString::Printf(TEXT("Boss Pattern : %s"), TEXT("Tentacle"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Boss_Gimmick_Gas()
{
	if (BossCharacter == nullptr)
	{
		BossCharacter = Cast<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));

		if (BossCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	BossCharacter->TestPattern(EBossPattern::GreenFog);
	message = FString::Printf(TEXT("Boss Pattern : %s"), TEXT("GreenFog"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Player_Log_HP()
{
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<APPCharacterPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterPlayer::StaticClass()));

		if (PlayerCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	message = FString::Printf(TEXT("Player HP : %f"), PlayerCharacter->GetCurrentHealth());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Player_Increase_HP(float value)
{
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<APPCharacterPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterPlayer::StaticClass()));

		if (PlayerCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	PlayerCharacter->IncreaseHealth(value);
	message = FString::Printf(TEXT("Increased Player HP : %f"), PlayerCharacter->GetCurrentHealth());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}

void UPPGameInstance::PP_Player_Decrease_HP(float value)
{
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<APPCharacterPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterPlayer::StaticClass()));

		if (PlayerCharacter == nullptr)
		{
			message = FString::Printf(TEXT("Actor is Missing!"));
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message);
			return;
		}
	}
	PlayerCharacter->DecreaseHealth(value);
	message = FString::Printf(TEXT("Decreased Player HP : %f"), PlayerCharacter->GetCurrentHealth());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, message);
}