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
		PauseWidget->PassSubWidgetTypeDelegate.AddUObject(this, &APPPauseWidgetActor::OpenSubWidget);
		PauseWidget->ExitGameDelegate.AddUObject(this, &APPPauseWidgetActor::EntryLobbyLevelSequence);
		SettingWidget->MainWidgetDelegate.AddUObject(this, &APPPauseWidgetActor::ReturnFromSettingToPause);
	}
	SettingWidgetActor->SetVisibility(false);
	SettingWidgetActor->SetActive(false);
	
	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPPauseWidgetActor::ClearAllTimerOnLevelChange);
}

void APPPauseWidgetActor::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
	GetWorldTimerManager().ClearTimer(EntryLobbyLevelAnimationTimer);
	WidgetAnimationTimer.Invalidate();
	EntryLobbyLevelAnimationTimer.Invalidate();
}

void APPPauseWidgetActor::OpenSubWidget(ESubWidgetType SubWidget)
{
	UGameplayStatics::PlaySound2D(GetWorld(), WidgetMoveSoundCue);
	
	if(SubWidget == ESubWidgetType::Setting)
	{
		PauseWidgetComponent->SetVisibility(false);
		PauseWidgetComponent->SetActive(false);
		PauseWidgetComponent->SetRelativeLocation(PauseWidgetComponent->GetRelativeLocation() + FVector(-2.0f,0.0f,0.0f));
		SettingWidgetActor->SetVisibility(true);
		SettingWidgetActor->SetActive(true);
		SettingWidgetActor->SetRelativeLocation(SettingWidgetActor->GetRelativeLocation() + FVector(2.0f,0.0f,0.0f));
	}
	else // (SubWidget == ESubWidgetType::Exit)
	{
		// 시간 되면 위젯 추가로 만들고 일단은 패스
		// ExitWidgetComponent->SetVisibility(true);
		GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
		UGameplayStatics::OpenLevel(this, MAIN_LEVEL);
	}
}

void APPPauseWidgetActor::ReturnFromSettingToPause()
{
	UGameplayStatics::PlaySound2D(GetWorld(), WidgetMoveSoundCue);

	PauseWidgetComponent->SetVisibility(true);
	PauseWidgetComponent->SetActive(true);
	PauseWidgetComponent->SetRelativeLocation(PauseWidgetComponent->GetRelativeLocation() + FVector(2.0f,0.0f,0.0f));
	SettingWidgetActor->SetVisibility(false);
	SettingWidgetActor->SetActive(false);
	SettingWidgetActor->SetRelativeLocation(SettingWidgetActor->GetRelativeLocation() + FVector(-2.0f,0.0f,0.0f));
}

void APPPauseWidgetActor::EntryLobbyLevelSequence()
{
	GetWorldTimerManager().SetTimer(EntryLobbyLevelAnimationTimer, FTimerDelegate::CreateLambda([&]()
	{
		if(true)
		{
			GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
			UGameplayStatics::OpenLevel(this, MAIN_LEVEL);
		}
	}), 0.01f, true);
}

