// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Pause/PPPauseWidgetActor.h"

#include "PPPauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"

// Sets default values
APPPauseWidgetActor::APPPauseWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PauseWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PauseUIWidget"));
	SettingWidgetActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("SettingWidget"));

	PauseWidgetComponent->SetupAttachment(RootComponent);
	SettingWidgetActor->SetupAttachment(RootComponent);
	
	PauseWidgetComponent->SetCastShadow(false);
}

// Called when the game starts or when spawned
void APPPauseWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	SetTickableWhenPaused(true);
	
	PauseWidget = CastChecked<UPPPauseWidget>(PauseWidgetComponent->GetUserWidgetObject());
	SettingWidget = CastChecked<APPSettingBaseActor>(SettingWidgetActor->GetChildActor());
	if(PauseWidget && SettingWidget)
	{
		PauseWidget->ResumeGameDelegate.AddUObject(this, &APPPauseWidgetActor::ResumeGame);
		PauseWidget->PassSubWidgetTypeDelegate.AddUObject(this, &APPPauseWidgetActor::OpenSubWidget);
		PauseWidget->ExitGameDelegate.AddUObject(this, &APPPauseWidgetActor::EntryLobbyLevel);
		SettingWidget->MainWidgetDelegate.AddUObject(this, &APPPauseWidgetActor::ReturnFromSettingToPause);
	}
	SettingWidgetActor->SetVisibility(false);
	
	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPPauseWidgetActor::ClearAllTimerOnLevelChange);
}

void APPPauseWidgetActor::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(EntryLobbyLevelAnimationTimer);
	EntryLobbyLevelAnimationTimer.Invalidate();
}

void APPPauseWidgetActor::ResumeGame()
{
	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, -10000.0f));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void APPPauseWidgetActor::OpenSubWidget(ESubWidgetType SubWidget)
{
	if(SubWidget == ESubWidgetType::Setting)
	{
		PauseWidgetComponent->SetVisibility(false);
		PauseWidgetComponent->AddRelativeLocation(FVector(5.0f,0.0f,0.0f));
		SettingWidgetActor->SetVisibility(true);
		SettingWidgetActor->AddRelativeLocation(FVector(-5.0f,0.0f,0.0f));
	}
	else // (SubWidget == ESubWidgetType::Exit)
	{
		// 시간 되면 위젯 추가로 만들고 일단은 패스
		// ExitWidgetComponent->SetVisibility(true);
		FString LevelName = UGameplayStatics::GetCurrentLevelName(this);
		if(LevelName == MAIN_LEVEL)
		{
			GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
			UGameplayStatics::OpenLevel(this, LOBBY_LEVEL);
		}
	}
}

void APPPauseWidgetActor::ReturnFromSettingToPause()
{
	PauseWidgetComponent->SetVisibility(true);
	PauseWidgetComponent->AddRelativeLocation(FVector(-5.0f,0.0f,0.0f));
	SettingWidgetActor->SetVisibility(false);
	SettingWidgetActor->AddRelativeLocation(FVector(5.0f,0.0f,0.0f));
}

void APPPauseWidgetActor::EntryLobbyLevel()
{
	GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
	UGameplayStatics::OpenLevel(this, LOBBY_LEVEL);
	/*
	FString LevelName = UGameplayStatics::GetCurrentLevelName(this);
	if(LevelName == MAIN_LEVEL || LevelName == TEST_MERGED_LEVEL)
	{
		GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
		UGameplayStatics::OpenLevel(this, LOBBY_LEVEL);
	}
	*/
}

