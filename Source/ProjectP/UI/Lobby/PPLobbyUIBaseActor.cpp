// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectP/UI/Lobby/PPLobbyUIBaseActor.h"

#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/UI/Lobby/PPLobbyUIWidget.h"
#include "Sound/SoundCue.h"

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
	SetTickableWhenPaused(true);
	
	LobbyWidget = CastChecked<UPPLobbyUIWidget>(LobbyWidgetComponent->GetUserWidgetObject());
	SettingWidget = CastChecked<APPSettingBaseActor>(SettingWidgetActor->GetChildActor());
	if(LobbyWidget && SettingWidget)
	{
		LobbyWidget->PassSubWidgetTypeDelegate.AddUObject(this, &APPLobbyUIBaseActor::OpenSubWidget);
		LobbyWidget->StartGameDelegate.AddUObject(this, &APPLobbyUIBaseActor::EntryMainLevelSequence);
		SettingWidget->MainWidgetDelegate.AddUObject(this, &APPLobbyUIBaseActor::ReturnFromSettingToLobby);
	}
	SettingWidgetActor->SetVisibility(false);
	ExitWidgetComponent->SetVisibility(false);

	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPLobbyUIBaseActor::ClearAllTimerOnLevelChange);

	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	WidgetMoveSoundCue = SoundData->WidgetMoveSoundCue;

	PostProcessVolume = Cast<APostProcessVolume>(GetWorld()->PostProcessVolumes[0]);
}

void APPLobbyUIBaseActor::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
	GetWorldTimerManager().ClearTimer(EntryMainLevelAnimationTimer);
	GetWorldTimerManager().ClearTimer(ExitGameFadeOutTimer);
	WidgetAnimationTimer.Invalidate();
	EntryMainLevelAnimationTimer.Invalidate();
	ExitGameFadeOutTimer.Invalidate();
}

void APPLobbyUIBaseActor::OpenSubWidget(ESubWidgetType SubWidget)
{
	UGameplayStatics::PlaySound2D(GetWorld(), WidgetMoveSoundCue);
	
	if(SubWidget == ESubWidgetType::Setting)
	{
		LobbyWidget->SetButtonInteraction(false);
		SettingWidgetActor->SetVisibility(true);
		CurrentLocation = GetActorLocation();
		GetWorldTimerManager().SetTimer(WidgetAnimationTimer, this, &APPLobbyUIBaseActor::OpenSettingWidgetDelegate, WidgetAnimationTick, true);
		return;
	}
	if(SubWidget == ESubWidgetType::Exit)
	{
		// 시간 되면 위젯 추가로 만들고 일단은 패스
		// ExitWidgetComponent->SetVisibility(true);
		DisableInput(GetWorld()->GetFirstPlayerController());
		GetWorldTimerManager().SetTimer(ExitGameFadeOutTimer, this, &APPLobbyUIBaseActor::OpenExitWidgetDelegate, 0.01f, true);
	}
}

void APPLobbyUIBaseActor::ReturnFromSettingToLobby()
{
	UGameplayStatics::PlaySound2D(GetWorld(), WidgetMoveSoundCue);
	
	CurrentLocation = GetActorLocation();
	LobbyWidgetComponent->SetVisibility(true);
	GetWorldTimerManager().SetTimer(WidgetAnimationTimer, this, &APPLobbyUIBaseActor::ReturnFromSettingToLobbyDelegate, WidgetAnimationTick, true);
}

void APPLobbyUIBaseActor::EntryMainLevelSequence()
{
	GetWorldTimerManager().SetTimer(EntryMainLevelAnimationTimer, this, &APPLobbyUIBaseActor::EntryMainLevelSequenceDelegate, 0.01f, true);
}

//----------------------Delegates------------------------------
void APPLobbyUIBaseActor::OpenSettingWidgetDelegate()
{
	AddActorLocalOffset(FVector(0.0f, -WidgetAnimationMoveValue, 0.0f));
	if (CurrentLocation.Y - WidgetMaximumMovementAmount >= GetActorLocation().Y)
	{
		SetActorLocation(CurrentLocation + FVector(0.0f, -WidgetMaximumMovementAmount, 0.0f));
		CurrentLocation = GetActorLocation();
		LobbyWidgetComponent->SetVisibility(false);
		LobbyWidget->SetButtonInteraction(true);
		GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
	}
}

void APPLobbyUIBaseActor::OpenExitWidgetDelegate()
{
	if (PostProcessVolume->Settings.AutoExposureBias <= -5.0f && PostProcessVolume->Settings.VignetteIntensity >= 2.5f)
	{
		GetWorldTimerManager().ClearTimer(ExitGameFadeOutTimer);
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
		return;
	}
	PostProcessVolume->Settings.AutoExposureBias -= 0.02f;
	PostProcessVolume->Settings.VignetteIntensity += 0.01f;
}

void APPLobbyUIBaseActor::ReturnFromSettingToLobbyDelegate()
{
	AddActorLocalOffset(FVector(0.0f, WidgetAnimationMoveValue, 0.0f));
	if (CurrentLocation.Y + WidgetMaximumMovementAmount <= GetActorLocation().Y)
	{
		SetActorLocation(CurrentLocation + FVector(0.0f, WidgetMaximumMovementAmount, 0.0f));
		CurrentLocation = GetActorLocation();
		SettingWidgetActor->SetVisibility(false);
		GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
	}
}

void APPLobbyUIBaseActor::EntryMainLevelSequenceDelegate()
{
	LobbyWidget->AddWidgetHeightOffset(5.0f);
	if (LobbyWidget->GetSubWidgetHeight() >= LobbyWidgetMaximumHeight)
	{
		LobbyWidget->SetWidgetHeightOffset(LobbyWidgetMaximumHeight);
		// Level Blueprint Delegate
		EntryMainLevelDelegate.Broadcast();
		GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
	}
}




