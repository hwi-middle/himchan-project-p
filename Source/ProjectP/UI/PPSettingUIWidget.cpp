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
	if(!IsChecked)
	{
		MasterSoundVolumeSlider->SetLocked(true);
	}
	else
	{
		MasterSoundVolumeSlider->SetLocked(false);
	}
}

void UPPSettingUIWidget::ApplyBgmSoundToggle(bool IsChecked)
{
	if(!IsChecked)
	{
		BgmSoundVolumeSlider->SetLocked(true);
	}
	else
	{
		BgmSoundVolumeSlider->SetLocked(false);
	}
}

void UPPSettingUIWidget::ApplySFXSoundToggle(bool IsChecked)
{
	if(!IsChecked)
	{
		SFXSoundVolumeSlider->SetLocked(true);
	}
	else
	{
		SFXSoundVolumeSlider->SetLocked(false);
	}
}
