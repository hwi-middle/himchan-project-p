// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/Lobby/PPLobbyUIBaseActor.h"
#include "ProjectP/UI/Lobby/PPLobbyUIWidget.h"
// Sets default values
APPLobbyUIBaseActor::APPLobbyUIBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	LobbyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LobbyUIWidget"));
	SettingWidgetActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("SettingWidget"));
	ExitWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ExitUIWidget"));

	LobbyWidgetComponent->SetupAttachment(RootComponent);
	SettingWidgetActor->SetupAttachment(RootComponent);
	ExitWidgetComponent->SetupAttachment(RootComponent);
	
	LobbyWidgetComponent->SetCastShadow(false);
	ExitWidgetComponent->SetCastShadow(false);
}

// Called when the game starts or when spawned
void APPLobbyUIBaseActor::BeginPlay()
{
	Super::BeginPlay();
	LobbyWidget = CastChecked<UPPLobbyUIWidget>(LobbyWidgetComponent->GetUserWidgetObject());
	SettingWidget = CastChecked<APPSettingBaseActor>(SettingWidgetActor->GetChildActor());
	if(LobbyWidget && SettingWidget)
	{
		LobbyWidget->PassSubWidgetTypeDelegate.AddUObject(this, &APPLobbyUIBaseActor::OpenSubWidget);
		SettingWidget->MainWidgetDelegate.AddUObject(this, &APPLobbyUIBaseActor::ReturnFromSettingToLobby);
	}
	SettingWidgetActor->SetVisibility(false);
	ExitWidgetComponent->SetVisibility(false);
}

void APPLobbyUIBaseActor::OpenSubWidget(ESubWidgetType SubWidget)
{
	if(SubWidget == ESubWidgetType::Setting)
	{
		LobbyWidget->SetButtonInteraction(false);
		SettingWidgetActor->SetVisibility(true);
		CurrentLocation = GetActorLocation();
		GetWorldTimerManager().SetTimer(WidgetAnimationTimer, FTimerDelegate::CreateLambda([&]()
		{
			AddActorLocalOffset(FVector(0.0f, -WidgetAnimationMoveValue, 0.0f));
			if(CurrentLocation.Y - WidgetMaximumMovementAmount >= GetActorLocation().Y)
			{
				SetActorLocation(CurrentLocation + FVector(0.0f, -WidgetMaximumMovementAmount, 0.0f));
				CurrentLocation = GetActorLocation();
				LobbyWidgetComponent->SetVisibility(false);
				LobbyWidget->SetButtonInteraction(true);
				GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
			}
		}), WidgetAnimationTick, true);
	}
	if(SubWidget == ESubWidgetType::Exit)
	{
		// 시간 되면 위젯 추가로 만들고 일단은 패스
		// ExitWidgetComponent->SetVisibility(true);
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
	}
}

void APPLobbyUIBaseActor::ReturnFromSettingToLobby()
{
	CurrentLocation = GetActorLocation();
	LobbyWidgetComponent->SetVisibility(true);
	GetWorldTimerManager().SetTimer(WidgetAnimationTimer, FTimerDelegate::CreateLambda([&]()
	{
		AddActorLocalOffset(FVector(0.0f, WidgetAnimationMoveValue, 0.0f));
		if(CurrentLocation.Y + WidgetMaximumMovementAmount <= GetActorLocation().Y)
		{
			SetActorLocation(CurrentLocation + FVector(0.0f, WidgetMaximumMovementAmount, 0.0f));
			CurrentLocation = GetActorLocation();
			SettingWidgetActor->SetVisibility(false);
			GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
		}
	}), WidgetAnimationTick, true);
}




