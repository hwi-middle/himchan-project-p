// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPLobbyWidget.h"

#include "Components/Button.h"

UPPLobbyWidget::UPPLobbyWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UPPLobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	StartButton->OnClicked.AddDynamic(this, &UPPLobbyWidget::EntryMainLevel);
	SettingButton->OnClicked.AddDynamic(this, &UPPLobbyWidget::OpenSettingWidget);
	HelpButton->OnClicked.AddDynamic(this, &UPPLobbyWidget::OpenHelpWidget);
	ExitButton->OnClicked.AddDynamic(this, &UPPLobbyWidget::UPPLobbyWidget::OpenExitCheckWidget);
}

void UPPLobbyWidget::EntryMainLevel()
{
	
}

void UPPLobbyWidget::OpenSettingWidget()
{
	
}

void UPPLobbyWidget::OpenHelpWidget()
{
	
}

void UPPLobbyWidget::OpenExitCheckWidget()
{
	
}
