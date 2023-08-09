// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSubtitleSettingWidget.h"

void UPPSubtitleSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SubtitleSmallFontSizeButton->OnClicked.AddDynamic(this, &UPPSubtitleSettingWidget::ApplySubtitleFontSizeSmall);
	SubtitleNormalFontSizeButton->OnClicked.AddDynamic(this, &UPPSubtitleSettingWidget::ApplySubtitleFontSizeNormal);
	SubtitleLargeFontSizeButton->OnClicked.AddDynamic(this, &UPPSubtitleSettingWidget::ApplySubtitleFontSizeLarge);

	UE_LOG(LogTemp, Log, TEXT("Current Font Size: %f"), GEngine->GetSubtitleFont()->GetFontScalingFactor());
}

void UPPSubtitleSettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	
}

void UPPSubtitleSettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	
}

void UPPSubtitleSettingWidget::ApplySubtitleFontSizeSmall()
{
	SubtitleSmallFontSizeButton->SetIsEnabled(false);
	SubtitleNormalFontSizeButton->SetIsEnabled(true);
	SubtitleLargeFontSizeButton->SetIsEnabled(true);
}

void UPPSubtitleSettingWidget::ApplySubtitleFontSizeNormal()
{
	SubtitleSmallFontSizeButton->SetIsEnabled(true);
	SubtitleNormalFontSizeButton->SetIsEnabled(false);
	SubtitleLargeFontSizeButton->SetIsEnabled(true);
}

void UPPSubtitleSettingWidget::ApplySubtitleFontSizeLarge()
{
	SubtitleSmallFontSizeButton->SetIsEnabled(true);
	SubtitleNormalFontSizeButton->SetIsEnabled(true);
	SubtitleLargeFontSizeButton->SetIsEnabled(false);
}
