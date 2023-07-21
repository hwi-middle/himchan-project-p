// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectP/UI/PPLobbyUIBaseActor.h"
#include "PPHelpUIWidget.h"
#include "PPSettingUIWidget.h"
#include "PPExitCheckUIWidget.h"
#include "PPLobbyUIWidget.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPLobbyUIBaseActor::APPLobbyUIBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LobbyUIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LobbyUIWidget"));
	LobbyUIWidget->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPLobbyUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/LobbyUIBlueprint.LobbyUIBlueprint_C'")));
	RootComponent = LobbyUIWidget;

	SettingUIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SettingUIWidget"));
	SettingUIWidget->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPSettingUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/SettingUIBlueprint.SettingUIBlueprint_C'")));
	SettingUIWidget->SetupAttachment(LobbyUIWidget);

	HelpUIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HelpUIWidget"));
	HelpUIWidget->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPHelpUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/HelpUIBlueprint.HelpUIBlueprint_C'")));
	HelpUIWidget->SetupAttachment(LobbyUIWidget);

	ExitCheckUIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ExitCheckUIWidget"));
	ExitCheckUIWidget->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPExitCheckUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/ExitCheckUIBlueprint.ExitCheckUIBlueprint_C'")));
	ExitCheckUIWidget->SetupAttachment(LobbyUIWidget);
	
}

void APPLobbyUIBaseActor::ToggleSettingWidgetVisible()
{
	SettingUIWidget->IsVisible() ? SettingUIWidget->SetVisibility(false) : SettingUIWidget->SetVisibility(true);
}

void APPLobbyUIBaseActor::ToggleHelpWidgetVisible()
{
	HelpUIWidget->IsVisible() ? HelpUIWidget->SetVisibility(false) : HelpUIWidget->SetVisibility(true);
}

void APPLobbyUIBaseActor::ToggleExitCheckWidgetVisible()
{
	ExitCheckUIWidget->IsVisible() ? ExitCheckUIWidget->SetVisibility(false) : ExitCheckUIWidget->SetVisibility(true);
}

// Called when the game starts or when spawned
void APPLobbyUIBaseActor::BeginPlay()
{
	Super::BeginPlay();

	SettingUIWidget->SetVisibility(false);
	HelpUIWidget->SetVisibility(false);
}


