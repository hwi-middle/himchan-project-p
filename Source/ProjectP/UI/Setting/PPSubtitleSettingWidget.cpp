// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSubtitleSettingWidget.h"

void UPPSubtitleSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SubtitleSmallFontSizeButton->OnCheckStateChanged.AddDynamic(this, &UPPSubtitleSettingWidget::ApplySubtitleFontSizeSmall);
	SubtitleNormalFontSizeButton->OnCheckStateChanged.AddDynamic(this, &UPPSubtitleSettingWidget::ApplySubtitleFontSizeNormal);
	SubtitleLargeFontSizeButton->OnCheckStateChanged.AddDynamic(this, &UPPSubtitleSettingWidget::ApplySubtitleFontSizeLarge);

	UE_LOG(LogTemp, Log, TEXT("Current Font Size: %f"), GEngine->GetSubtitleFont()->GetFontScalingFactor());
}

void UPPSubtitleSettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	
}

void UPPSubtitleSettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	
}

void UPPSubtitleSettingWidget::ApplySubtitleFontSizeSmall(const bool IsChecked)
{
	if(IsChecked)
	{
		SubtitleNormalFontSizeButton->SetIsChecked(false);
		SubtitleLargeFontSizeButton->SetIsChecked(false);
	}
}

void UPPSubtitleSettingWidget::ApplySubtitleFontSizeNormal(const bool IsChecked)
{
	if(IsChecked)
	{
		SubtitleNormalFontSizeButton->SetIsChecked(false);
		SubtitleLargeFontSizeButton->SetIsChecked(false);
	}
}

void UPPSubtitleSettingWidget::ApplySubtitleFontSizeLarge(const bool IsChecked)
{
	if(IsChecked)
	{
		SubtitleNormalFontSizeButton->SetIsChecked(false);
		SubtitleLargeFontSizeButton->SetIsChecked(false);
	}
}
