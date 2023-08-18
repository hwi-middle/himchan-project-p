// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/Lobby/PPLobbyUIWidget.h"
#include "EngineUtils.h"
#include "ProjectP/Game/PPGameInstance.h"

void UPPLobbyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	StartButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::EntryMainLevel);
	SettingButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::ActivateSettingWidget);
	ExitButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::ActivateExitWidget);
}

void UPPLobbyUIWidget::SetButtonInteraction(bool bInteraction)
{
	StartButton->SetIsEnabled(bInteraction);
	SettingButton->SetIsEnabled(bInteraction);
	ExitButton->SetIsEnabled(bInteraction);
}

void UPPLobbyUIWidget::EntryMainLevel()
{
	GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
	UGameplayStatics::OpenLevel(this, MAIN_LEVEL);
}
