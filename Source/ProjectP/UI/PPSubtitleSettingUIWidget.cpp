// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPSubtitleSettingUIWidget.h"

void UPPSubtitleSettingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ApplySubtitleFontSizeLarge();
	// 예상값: 96
	UE_LOG(LogTemp, Log, TEXT("Current Font Size: %f"), GEngine->GetSubtitleFont()->GetFontScalingFactor());
}
