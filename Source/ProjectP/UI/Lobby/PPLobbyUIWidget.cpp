// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/Lobby/PPLobbyUIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPPLobbyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	StartButton->OnClicked.AddDynamic(this, &UPPLobbyUIWidget::EntryMainLevel);
}

void UPPLobbyUIWidget::EntryMainLevel()
{
	UGameplayStatics::OpenLevel(this, "EntryMapTest");
}