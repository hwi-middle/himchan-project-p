// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSettingBaseActor.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Game/PPGameInstance.h"

/*
*
───────────────────────────────────────
───▐▀▄───────▄▀▌───▄▄▄▄▄▄▄─────────────
───▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄──────────
──▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄────────
──▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄──────
▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌─────
▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐───▄▄
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀─
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀───
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌────
─▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐─────
─▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌─────
──▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐──────
──▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌──────
────▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀────────
 */

// Sets default values
APPSettingBaseActor::APPSettingBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SettingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SettingWidget"));
	RootComponent = SettingWidgetComponent;
}

// Called when the game starts or when spawned
void APPSettingBaseActor::BeginPlay()
{
	Super::BeginPlay();
	SetTickableWhenPaused(true);
	
	SettingWidget = CastChecked<UPPSettingUIWidget>(SettingWidgetComponent->GetUserWidgetObject());
	SettingWidget->PassSubWidgetTypeDelegate.AddUObject(this, &APPSettingBaseActor::OpenSubWidget);
	SettingWidget->LoadMainWidgetDelegate.AddUObject(this, &APPSettingBaseActor::ExitButtonBroadcast);
	SettingWidget->SetSubWidgetPanelVisible(false);

	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPSettingBaseActor::ClearAllTimerOnLevelChange);

	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	WidgetOpenSoundCue = SoundData->WidgetOpenSoundCue;
	WidgetCloseSoundCue = SoundData->WidgetCloseSoundCue;
	
	bSubWidgetOpened = false;
	bIsFirstClick = true;
}

void APPSettingBaseActor::ClearAllTimerOnLevelChange()
{
	SettingWidget->SaveSettingData();
	GetWorldTimerManager().ClearTimer(SubWidgetOpenTimer);
	GetWorldTimerManager().ClearTimer(SubWidgetCloseTimer);
	SubWidgetOpenTimer.Invalidate();
	SubWidgetCloseTimer.Invalidate();
}

void APPSettingBaseActor::ExitButtonBroadcast()
{
	SwapSubWidget = ESubWidgetType::None;
	bIsFirstClick = true;
	if(bSubWidgetOpened)
	{
		SettingWidget->SaveSettingData();
		CloseSubWidgetPanel();
	}
	MainWidgetDelegate.Broadcast();
}

void APPSettingBaseActor::OpenSubWidget(ESubWidgetType SubWidget)
{
	if(bIsFirstClick)
	{
		SettingWidget->SetSubWidgetPanelVisible(true);
		SettingWidget->SetSubWidgetContent(SubWidget);
		SettingWidget->SetSubWidgetHeightOffset(SubWidgetHalfHeightValue);
		OpenSubWidgetPanel();
		bIsFirstClick = false;
		return;
	}
	// 이미 서브위젯이 열려있는 상태로 해당 함수가 실행되면 닫기 애니메이션 후 서브위젯 변경
	if(bSubWidgetOpened)
	{
		SwapSubWidget = SubWidget;
		SettingWidget->SaveSettingData();
		CloseSubWidgetPanel();
	}
	else
	{
		SettingWidget->SetSubWidgetContent(SubWidget);
		OpenSubWidgetPanel();
	}
}

void APPSettingBaseActor::CloseSubWidgetPanel()
{

	if(UGameplayStatics::GetGlobalTimeDilation(GetWorld()) != 1.0f)
	{
		SettingWidget->SetSubWidgetContentVisible(false);
		SettingWidget->SetSubWidgetAnimationWorking(false);
		SettingWidget->SetSubWidgetHeightOffset(SubWidgetHalfHeightValue);
		bSubWidgetOpened = false;
		if(SwapSubWidget != ESubWidgetType::None)
		{
			OpenSubWidget(SwapSubWidget);
		}
		return;
	}

	UGameplayStatics::PlaySound2D(this, WidgetCloseSoundCue);
	
	SettingWidget->SetSubWidgetContentVisible(false);
	SettingWidget->SetSubWidgetAnimationWorking(true);

	// 서브위젯 닫기 애니메이션.
	GetWorldTimerManager().SetTimer(SubWidgetCloseTimer, FTimerDelegate::CreateLambda([&]()
	{
		SettingWidget->AddSubWidgetHeightOffset(WidgetHeightOffsetAddValue);
		if(SettingWidget->GetSubWidgetHeight() >= SubWidgetHalfHeightValue)
		{
			SettingWidget->SetSubWidgetHeightOffset(SubWidgetHalfHeightValue);
			bSubWidgetOpened = false;
			SettingWidget->SetSubWidgetAnimationWorking(false);
			// 전환하는 서브위젯이 있다면 다시 서브위젯 패널 열기.
			// 왜 이런 고생을 하느냐면 멋지니까?
			if(SwapSubWidget != ESubWidgetType::None)
			{
				OpenSubWidget(SwapSubWidget);
			}
			GetWorldTimerManager().ClearTimer(SubWidgetCloseTimer);
		}
	}), WidgetAnimationTick, true);
}

void APPSettingBaseActor::OpenSubWidgetPanel()
{
	UGameplayStatics::PlaySound2D(this, WidgetOpenSoundCue);

	if(UGameplayStatics::GetGlobalTimeDilation(GetWorld()) != 1.0f)
	{
		SettingWidget->SetSubWidgetHeightOffset(0.0f);
		SettingWidget->SetSubWidgetContentVisible(true);
		SettingWidget->SetSubWidgetAnimationWorking(false);
		bSubWidgetOpened = true;
		return;
	}
	
	SettingWidget->SetSubWidgetAnimationWorking(true);
	// 서브위젯 열기 애니메이션
	GetWorldTimerManager().SetTimer(SubWidgetOpenTimer, FTimerDelegate::CreateLambda([&]()
	{
		SettingWidget->AddSubWidgetHeightOffset(-WidgetHeightOffsetAddValue);
		if(SettingWidget->GetSubWidgetHeight() <= 0.0f)
		{
			SettingWidget->SetSubWidgetHeightOffset(0.0f);
			SettingWidget->SetSubWidgetContentVisible(true);
			bSubWidgetOpened = true;
			SettingWidget->SetSubWidgetAnimationWorking(false);
			GetWorldTimerManager().ClearTimer(SubWidgetOpenTimer);
		}
	}), WidgetAnimationTick, true);
}
