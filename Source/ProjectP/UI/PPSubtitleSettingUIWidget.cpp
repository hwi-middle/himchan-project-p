// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPSubtitleSettingUIWidget.h"

void UPPSubtitleSettingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SubtitleSmallFontSizeButton->OnClicked.AddDynamic(this, &UPPSubtitleSettingUIWidget::ApplySubtitleFontSizeSmall);
	SubtitleNormalFontSizeButton->OnClicked.AddDynamic(this, &UPPSubtitleSettingUIWidget::ApplySubtitleFontSizeNormal);
	SubtitleLargeFontSizeButton->OnClicked.AddDynamic(this, &UPPSubtitleSettingUIWidget::ApplySubtitleFontSizeLarge);

	UE_LOG(LogTemp, Log, TEXT("Current Font Size: %f"), GEngine->GetSubtitleFont()->GetFontScalingFactor());
}
