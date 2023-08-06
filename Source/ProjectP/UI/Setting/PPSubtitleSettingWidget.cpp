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
