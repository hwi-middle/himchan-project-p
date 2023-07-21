// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/PPLobbyUIWidget.h"

#include "PPSettingUIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPPLobbyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	StartButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::EntryMainLevel);
	SettingButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::ToggleSettingWidget);
	HelpButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::ToggleHelpWidget);
	ExitButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::OpenExitCheckWidget);
}

void UPPLobbyUIWidget::EntryMainLevel()
{
	// 레벨 전환 효과를 어떻게 할진 기획 파트와 상의?
	UGameplayStatics::OpenLevel(this, "EntryMapTest");
}

void UPPLobbyUIWidget::ToggleSettingWidget()
{
	
}

void UPPLobbyUIWidget::ToggleHelpWidget()
{
	
}

void UPPLobbyUIWidget::OpenExitCheckWidget()
{
	
}