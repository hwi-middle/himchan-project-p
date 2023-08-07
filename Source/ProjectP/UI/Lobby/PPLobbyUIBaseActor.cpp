// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/Lobby/PPLobbyUIBaseActor.h"
#include "PPLobbyUIWidget.h"
// Sets default values
APPLobbyUIBaseActor::APPLobbyUIBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LobbyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LobbyUIWidget"));
	RootComponent = LobbyWidgetComponent;

	LobbyWidgetComponent->SetCastShadow(false);
}

// Called when the game starts or when spawned
void APPLobbyUIBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APPLobbyUIBaseActor::ToggleWidgetVisible(const EWidgetType WidgetType)
{
	
}




