// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSettingUIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPSaveSettingOption.h"


void UPPSettingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OpenSoundSettingWidgetButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ActivateSoundSettingWidget);
	OpenDisplaySettingWidgetButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ActivateDisplaySettingWidget);
	OpenGraphicSettingWidgetButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ActivateGraphicSettingWidget);
	
	OpenAccessibilitySettingWidgetButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ActivateAccessibilitySettingWidget);
	/*
	OpenSubtitleSettingWidgetButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ActivateSubtitleSettingWidget);
	*/
	ExitSettingUIButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ExitSettingUI);
	SubWidgetPanelSlot = CastChecked<UCanvasPanelSlot>(SubWidgetPanel->Slot);
	
	SoundSettingWidget->SetIsEnabled(false);
	SoundSettingWidget->SetRenderOpacity(0.0f);
	DisplaySettingWidget->SetIsEnabled(false);
	DisplaySettingWidget->SetRenderOpacity(0.0f);
	GraphicSettingWidget->SetIsEnabled(false);
	GraphicSettingWidget->SetRenderOpacity(0.0f);
	AccessibilitySettingWidget->SetIsEnabled(false);
	AccessibilitySettingWidget->SetRenderOpacity(0.0f);
	/*
	SubtitleSettingWidget->SetIsEnabled(false);
	SubtitleSettingWidget->SetRenderOpacity(0.0f);
	*/
	EnabledSubWidgetType = ESubWidgetType::None;
	bSubWidgetAnimationWork = false;
	
	LoadSettingData();
}

void UPPSettingUIWidget::SaveSettingData()
{
	// 만약 게임 플레이 내용 저장/불러오기 기능을 구현한다고 해도 설정은 여러개 저장 할 일이 없기 때문에 인덱스 0 고정
	// 파일 이름 또한 마찬가지로 생성자에서 설정한 초기 값 사용
	TObjectPtr<UPPGameInstance> CurrentGI = CastChecked<UPPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<UPPSaveSettingOption> SaveSettingOption = CurrentGI->GetSaveSettingOption();
	if(SaveSettingOption)
	{
		// 서브위젯으로 세이브 전달
		SoundSettingWidget->SaveSettingData(SaveSettingOption);
		DisplaySettingWidget->SaveSettingData(SaveSettingOption);
		GraphicSettingWidget->SaveSettingData(SaveSettingOption);
		AccessibilitySettingWidget->SaveSettingData(SaveSettingOption);
		/*
		SubtitleSettingWidget->SaveSettingData(CurrentGI->SaveSettingOption);
		*/
		UGameplayStatics::SaveGameToSlot(SaveSettingOption, SaveSettingOption->SaveFileName, 0);
		UE_LOG(LogTemp, Log, TEXT("Save SettingOption Data Completed"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Save SettingOption Data invalied"));
	}
}

void UPPSettingUIWidget::LoadSettingData()
{
	const TObjectPtr<UPPGameInstance> CurrentGI = Cast<UPPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<UPPSaveSettingOption> SaveSettingOption = CurrentGI->GetSaveSettingOption();
	if(SaveSettingOption)
	{
		SoundSettingWidget->LoadSettingData(SaveSettingOption);
		DisplaySettingWidget->LoadSettingData(SaveSettingOption);
		GraphicSettingWidget->LoadSettingData(SaveSettingOption);
		AccessibilitySettingWidget->LoadSettingData(SaveSettingOption);
		/*
		SubtitleSettingWidget->LoadSettingData(CurrentGI->SaveSettingOption);
		*/
		UE_LOG(LogTemp, Log, TEXT("Load Setting Option SaveFile Completed"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Load Setting Option SaveFile Failed"));
	}
}

void UPPSettingUIWidget::SetSubWidgetContent(ESubWidgetType SubWidget)
{
	switch (SubWidget)
	{
	case ESubWidgetType::Sound:
		EnabledSubWidget = SoundSettingWidget;
		break;
	case  ESubWidgetType::Display:
		EnabledSubWidget = DisplaySettingWidget;
		break;
	case  ESubWidgetType::Graphic:
		EnabledSubWidget = GraphicSettingWidget;
		break;
	case  ESubWidgetType::Accessibility:
		EnabledSubWidget = AccessibilitySettingWidget;
		break;
	case  ESubWidgetType::Subtitle:
		// EnabledSubWidget = SubtitleSettingWidget;
		break;
	default:
		checkNoEntry();
	}
}

void UPPSettingUIWidget::SetSubWidgetContentVisible(const bool IsActivate)
{
	if(IsActivate)
	{
		EnabledSubWidget->SetIsEnabled(true);
		EnabledSubWidget->SetRenderOpacity(1.0f);
		Cast<UCanvasPanelSlot>(EnabledSubWidget->Slot)->SetZOrder(1);
	}
	else
	{
		EnabledSubWidget->SetIsEnabled(false);
		EnabledSubWidget->SetRenderOpacity(0.0f);
		Cast<UCanvasPanelSlot>(EnabledSubWidget->Slot)->SetZOrder(0);
	}
}

void UPPSettingUIWidget::ActivateSoundSettingWidget()
{
	if(!bSubWidgetAnimationWork)
	{
		PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Sound);
	}
}

void UPPSettingUIWidget::ActivateDisplaySettingWidget()
{
	if(!bSubWidgetAnimationWork)
	{
		PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Display);
	}
}

void UPPSettingUIWidget::ActivateGraphicSettingWidget()
{
	if(!bSubWidgetAnimationWork)
	{
		PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Graphic);
	}
}

void UPPSettingUIWidget::ActivateAccessibilitySettingWidget()
{
	if(!bSubWidgetAnimationWork)
	{
		PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Accessibility);
	}
}

void UPPSettingUIWidget::ActivateSubtitleSettingWidget()
{
	if(!bSubWidgetAnimationWork)
	{
		PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Subtitle);
	}
}

void UPPSettingUIWidget::ExitSettingUI()
{
	SaveSettingData();
	LoadMainWidgetDelegate.Broadcast();
}
