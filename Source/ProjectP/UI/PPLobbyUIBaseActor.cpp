// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectP/UI/PPLobbyUIBaseActor.h"
#include "PPTutorialUIWidget.h"
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

	TutorialWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TutorialUIWidget"));
	TutorialWidgetComponent->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPTutorialUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/TutorialWidgetBlueprint.TutorialWidgetBlueprint_C'")));
	TutorialWidgetComponent->SetupAttachment(LobbyWidgetComponent);

	ExitCheckWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ExitCheckUIWidget"));
	ExitCheckWidgetComponent->SetWidgetClass(FPPConstructorHelper::FindAndGetClass<UPPExitCheckUIWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/16-Lobby-UI/Blueprints/ExitCheckUIBlueprint.ExitCheckUIBlueprint_C'")));
	ExitCheckWidgetComponent->SetupAttachment(LobbyWidgetComponent);

	LobbyWidgetComponent->SetCastShadow(false);
	SettingWidgetComponent->SetCastShadow(false);
	TutorialWidgetComponent->SetCastShadow(false);
	ExitCheckWidgetComponent->SetCastShadow(false);
}

// Called when the game starts or when spawned
void APPLobbyUIBaseActor::BeginPlay()
{
	Super::BeginPlay();

	SettingWidgetComponent->SetVisibility(false);
	TutorialWidgetComponent->SetVisibility(false);

	TObjectPtr<UPPLobbyUIWidget> LobbyWidget = Cast<UPPLobbyUIWidget>(LobbyWidgetComponent->GetUserWidgetObject());
	if (LobbyWidget)
	{
		LobbyWidget->LobbyButtonDelegate.AddUObject(this, &APPLobbyUIBaseActor::ToggleWidgetVisible);
	}
	TObjectPtr<UPPSettingUIWidget> SettingUIWidget = Cast<UPPSettingUIWidget>(SettingWidgetComponent->GetUserWidgetObject());
	if(SettingUIWidget)
	{
		SettingUIWidget->SettingButtonDelegate.AddUObject(this, &APPLobbyUIBaseActor::ToggleWidgetVisible);
	}
	TObjectPtr<UPPTutorialUIWidget> TutorialUIWidget = Cast<UPPTutorialUIWidget>(TutorialWidgetComponent->GetUserWidgetObject());
	if(TutorialUIWidget)
	{
		TutorialUIWidget->TutorialButtonDelegate.AddUObject(this, &APPLobbyUIBaseActor::ToggleWidgetVisible);
	}
}

void APPLobbyUIBaseActor::ToggleWidgetVisible(const EWidgetType WidgetType)
{
	switch (WidgetType)
	{
	case EWidgetType::Setting:
		SettingWidgetComponent->SetVisibility(!SettingWidgetComponent->IsVisible());
		break;
	case EWidgetType::Tutorial:
		TutorialWidgetComponent->SetVisibility(!TutorialWidgetComponent->IsVisible());
		break;
	case EWidgetType::ExitCheck:
		ExitCheckWidgetComponent->SetVisibility(!ExitCheckWidgetComponent->IsVisible());
		break;
	default:
		checkNoEntry();
	}
}




