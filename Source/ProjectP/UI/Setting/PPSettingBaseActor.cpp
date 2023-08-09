// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSettingBaseActor.h"

// Sets default values
APPSettingBaseActor::APPSettingBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APPSettingBaseActor::BeginPlay()
{
	Super::BeginPlay();
	SettingWidget = CastChecked<UPPSettingUIWidget>(SettingWidgetComponent->GetUserWidgetObject());
	SettingWidget->PassSubWidgetTypeDelegate.AddUObject(this, &APPSettingBaseActor::OpenSubWidget);
}

void APPSettingBaseActor::OpenSubWidget(ESubWidgetType SubWidget)
{
	// 이미 서브위젯이 열려있는 상태로 실행되면 닫기 애니메이션 후 서브위젯 변경
	if(bSubWidgetOpened)
	{
		ToggleSubWidgetPanel(true, SubWidget);
	}
	else
	{
		SettingWidget->SetSubWidgetContent(SubWidget);
		ToggleSubWidgetPanel(false);
	}
}

void APPSettingBaseActor::ToggleSubWidgetPanel(const bool IsOpened, ESubWidgetType SwapSubWidget)
{
	if(IsOpened)
	{
		SettingWidget->SetSubWidgetContentVisible(false);
		// 서브위젯 닫기 애니메이션.
		GetWorldTimerManager().SetTimer(SubWidgetControlTimer, FTimerDelegate::CreateLambda([&]()
		{
			SettingWidget->AddSubWidgetHeight(-WidgetHeightAddValue);
			if(SettingWidget->GetSubWidgetHeight() <= 0.0f)
			{
				SettingWidget->SetSubWidgetHeight(0.0f);
				bSubWidgetOpened = false;
				// 전환하는 위젯이 있다면 다시 서브위젯 열기.
				// 왜 이런 고생을 하느냐면 멋지니까?
				if(SwapSubWidget != ESubWidgetType::None)
				{
					OpenSubWidget(SwapSubWidget);
				}
				GetWorldTimerManager().ClearTimer(SubWidgetControlTimer);
			}
		}), WidgetAnimationTick, true);
	}
	else
	{
		// 서브위젯 열기 애니메이션
		GetWorldTimerManager().SetTimer(SubWidgetControlTimer, FTimerDelegate::CreateLambda([&]()
		{
			SettingWidget->AddSubWidgetHeight(WidgetHeightAddValue);
			if(SettingWidget->GetSubWidgetHeight() >= WidgetHalfHeightValue)
			{
				SettingWidget->SetSubWidgetHeight(WidgetHalfHeightValue);
				SettingWidget->SetSubWidgetContentVisible(true);
				bSubWidgetOpened = true;
				GetWorldTimerManager().ClearTimer(SubWidgetControlTimer);
			}
		}), WidgetAnimationTick, true);
	}
}

// Called every frame
void APPSettingBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

