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

	LobbyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LobbyUIWidget"));
	LobbyWidgetComponent->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPLobbyUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/LobbyUIBlueprint.LobbyUIBlueprint_C'")));
	RootComponent = LobbyWidgetComponent;

	SettingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SettingUIWidget"));
	SettingWidgetComponent->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPSettingUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/SettingUIBlueprint.SettingUIBlueprint_C'")));
	SettingWidgetComponent->SetupAttachment(LobbyWidgetComponent);

	HelpWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HelpUIWidget"));
	HelpWidgetComponent->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPHelpUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/HelpUIBlueprint.HelpUIBlueprint_C'")));
	HelpWidgetComponent->SetupAttachment(LobbyWidgetComponent);

	ExitCheckWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ExitCheckUIWidget"));
	ExitCheckWidgetComponent->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPExitCheckUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/ExitCheckUIBlueprint.ExitCheckUIBlueprint_C'")));
	ExitCheckWidgetComponent->SetupAttachment(LobbyWidgetComponent);

	LobbyWidgetComponent->SetCastShadow(false);
	SettingWidgetComponent->SetCastShadow(false);
	HelpWidgetComponent->SetCastShadow(false);
	ExitCheckWidgetComponent->SetCastShadow(false);
}

void APPLobbyUIBaseActor::ToggleSettingWidgetVisible()
{
	SettingWidgetComponent->SetVisibility(!SettingWidgetComponent->IsVisible());
}

void APPLobbyUIBaseActor::ToggleHelpWidgetVisible()
{
	HelpWidgetComponent->SetVisibility(!HelpWidgetComponent->IsVisible());
}

void APPLobbyUIBaseActor::ToggleExitCheckWidgetVisible()
{
	ExitCheckWidgetComponent->SetVisibility(!ExitCheckWidgetComponent->IsVisible());
	
}

// Called when the game starts or when spawned
void APPLobbyUIBaseActor::BeginPlay()
{
	Super::BeginPlay();

	SettingWidgetComponent->SetVisibility(false);
	HelpWidgetComponent->SetVisibility(false);

	TObjectPtr<UClass> LobbyWidget = LobbyWidgetComponent->GetWidgetClass();
	if(LobbyWidget)
	{
		if (LobbyWidget->IsChildOf(UUserWidget::StaticClass()))
		{
			TObjectPtr<UPPLobbyUIWidget> UserWidget = Cast<UPPLobbyUIWidget>(LobbyWidgetComponent->GetUserWidgetObject());
			if (UserWidget)
			{
				UserWidget->LobbyUIBaseActor = this;
			}
		}
	}
	TObjectPtr<UPPSettingUIWidget> SettingUIWidget = Cast<UPPSettingUIWidget>(SettingWidgetComponent->GetUserWidgetObject());
	if(SettingUIWidget)
	{
		SettingUIWidget->SettingButtonDelegate.AddUObject(this, &APPLobbyUIBaseActor::ToggleHelpWidgetVisible);
	}
}


