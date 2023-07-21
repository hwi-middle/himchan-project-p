// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/PPLobbyUIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPPLobbyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	StartButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::EntryMainLevel);
	SettingButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::ToggleSettingWidget);
	HelpButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::ToggleHelpWidget);
	ExitButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::OpenExitCheckWidget);
	
	SettingDelegate.BindUObject(LobbyBaseActor, &APPLobbyUIBaseActor::ToggleSettingWidgetVisible);
	HelpDelegate.BindUObject(LobbyBaseActor, &APPLobbyUIBaseActor::ToggleHelpWidgetVisible);
	ExitDelegate.BindUObject(LobbyBaseActor, &APPLobbyUIBaseActor::ToggleExitCheckWidgetVisible);
}

void UPPLobbyUIWidget::EntryMainLevel()
{
	// 레벨 전환 효과를 어떻게 할진 기획 파트와 상의?
	UGameplayStatics::OpenLevel(this, "EntryMapTest");
}

void UPPLobbyUIWidget::ToggleSettingWidget()
{
	SettingDelegate.ExecuteIfBound();
}

void UPPLobbyUIWidget::ToggleHelpWidget()
{
	SettingDelegate.ExecuteIfBound();
}

void UPPLobbyUIWidget::OpenExitCheckWidget()
{
	SettingDelegate.ExecuteIfBound();
}