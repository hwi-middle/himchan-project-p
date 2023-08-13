// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/Lobby/PPLobbyUIBaseActor.h"
#include "PPLobbyUIWidget.h"
// Sets default values
APPLobbyUIBaseActor::APPLobbyUIBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LobbyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LobbyUIWidget"));
	SettingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SettingWidget"));
	RootComponent = LobbyWidgetComponent;

	LobbyWidgetComponent->SetCastShadow(false);
	SettingWidgetComponent->SetCastShadow(false);
}

// Called when the game starts or when spawned
void APPLobbyUIBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}




