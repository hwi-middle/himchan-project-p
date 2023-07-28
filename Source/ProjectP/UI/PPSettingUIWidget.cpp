// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPSettingUIWidget.h"

#include "Components/CheckBox.h"
#include "Components/Slider.h"

void UPPSettingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MasterSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyMasterSliderValue);
	BgmSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyMasterSliderValue);
	SFXSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplySFXSliderValue);

	MasterSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyMasterSoundToggle);
	BgmSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyBgmSoundToggle);
	SFXSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplySFXSoundToggle);

	DisplayBrightnessSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyDisplayBrightnessSliderValue);
	DisplayVignettingSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyDisplayVignettingSliderValue);

	PauseInterfaceDistanceSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyPauseInterfaceDistanceSliderValue);
	PauseInterfaceHeightSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyPauseInterfaceHeightSliderValue);

	LeftHandedSettingToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyLeftHandedSettingToggle);
	ControllerVibrationToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyControllerVibrationToggle);
}

void UPPSettingUIWidget::ApplyMasterSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyBgmSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplySFXSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyMasterSoundToggle(bool IsChecked)
{
	!IsChecked ? MasterSoundVolumeSlider->SetLocked(true) : MasterSoundVolumeSlider->SetLocked(false);
}

void UPPSettingUIWidget::ApplyBgmSoundToggle(bool IsChecked)
{
	!IsChecked ? BgmSoundVolumeSlider->SetLocked(true) : BgmSoundVolumeSlider->SetLocked(false);
}

void UPPSettingUIWidget::ApplySFXSoundToggle(bool IsChecked)
{
	!IsChecked ? SFXSoundVolumeSlider->SetLocked(true) : SFXSoundVolumeSlider->SetLocked(false);
}

void UPPSettingUIWidget::ApplyDisplayBrightnessSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyDisplayVignettingSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyPauseInterfaceDistanceSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyPauseInterfaceHeightSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyLeftHandedSettingToggle(bool IsChecked)
{
	LeftHandedSettingDelegate.ExecuteIfBound(IsChecked);
}

void UPPSettingUIWidget::ApplyControllerVibrationToggle(bool IsChecked)
{
	ControllerVibrationDelegate.ExecuteIfBound(IsChecked);
}
