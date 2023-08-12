// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPDisplaySettingWidget.h"
#include "Kismet/GameplayStatics.h"

void UPPDisplaySettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	TArray<AActor*> PostProcessVolumes;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), PostProcessVolumes);
	if(PostProcessVolumes.Num() > 0)
	{
		PostProcessVolume = Cast<APostProcessVolume>(PostProcessVolumes[0]);
		if(PostProcessVolume)
		{
			UE_LOG(LogTemp, Log, TEXT("Get World's PostProcessVolume Completed"));
		}
	}
	
	DisplayBrightnessSlider->OnValueChanged.AddDynamic(this, &UPPDisplaySettingWidget::ApplyDisplayBrightnessSliderValue);
	DisplayVignettingSlider->OnValueChanged.AddDynamic(this, &UPPDisplaySettingWidget::ApplyDisplayVignettingSliderValue);
}

void UPPDisplaySettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	SettingOption->DisplayBrightnessValue = DisplayBrightnessSlider->GetValue();
	SettingOption->DisplayVignettingValue = DisplayVignettingSlider->GetValue();
}

void UPPDisplaySettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	DisplayBrightnessSlider->SetValue(SettingOption->DisplayBrightnessValue);
	DisplayBrightnessSlider->OnValueChanged.Broadcast(DisplayBrightnessSlider->GetValue());
		
	DisplayVignettingSlider->SetValue(SettingOption->DisplayVignettingValue);
	DisplayVignettingSlider->OnValueChanged.Broadcast(DisplayVignettingSlider->GetValue());
}
