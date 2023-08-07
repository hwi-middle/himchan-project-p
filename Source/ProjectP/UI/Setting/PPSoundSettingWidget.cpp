// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSoundSettingWidget.h"

void UPPSoundSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MasterSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSoundSettingWidget::ApplyMasterSliderValue);
	BGMSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSoundSettingWidget::ApplyBGMSliderValue);
	SFXSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSoundSettingWidget::ApplySFXSliderValue);

	MasterSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSoundSettingWidget::ApplyMasterSoundToggle);
	BGMSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSoundSettingWidget::ApplyBGMSoundToggle);
	SFXSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSoundSettingWidget::ApplySFXSoundToggle);
}

void UPPSoundSettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	SettingOption->MasterSoundVolumeSliderValue = MasterSoundVolumeSlider->GetValue();
	SettingOption->BGMSoundVolumeSliderValue = BGMSoundVolumeSlider->GetValue();
	SettingOption->SFXSoundVolumeSliderValue = SFXSoundVolumeSlider->GetValue();
	SettingOption->bMasterSoundToggle = MasterSoundToggle->IsChecked();
	SettingOption->bBGMSoundToggle = BGMSoundToggle->IsChecked();
	SettingOption->bSFXSoundToggle = SFXSoundToggle->IsChecked();
}

void UPPSoundSettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	MasterSoundVolumeSlider->SetValue(SettingOption->MasterSoundVolumeSliderValue);
	MasterSoundVolumeSlider->OnValueChanged.Broadcast(MasterSoundVolumeSlider->GetValue());
		
	BGMSoundVolumeSlider->SetValue(SettingOption->BGMSoundVolumeSliderValue);
	BGMSoundVolumeSlider->OnValueChanged.Broadcast(BGMSoundVolumeSlider->GetValue());
		
	SFXSoundVolumeSlider->SetValue(SettingOption->SFXSoundVolumeSliderValue);
	SFXSoundVolumeSlider->OnValueChanged.Broadcast(SFXSoundVolumeSlider->GetValue());
		
	MasterSoundToggle->SetIsChecked(SettingOption->bMasterSoundToggle);
	MasterSoundToggle->OnCheckStateChanged.Broadcast(MasterSoundToggle->IsChecked());
		
	BGMSoundToggle->SetIsChecked(SettingOption->bBGMSoundToggle);
	BGMSoundToggle->OnCheckStateChanged.Broadcast(BGMSoundToggle->IsChecked());
		
	SFXSoundToggle->SetIsChecked(SettingOption->bSFXSoundToggle);
	SFXSoundToggle->OnCheckStateChanged.Broadcast(SFXSoundToggle->IsChecked());
}

void UPPSoundSettingWidget::ApplyMasterSoundToggle(bool IsChecked)
{
	if(IsChecked)
	{
		MasterSoundVolumeSlider->SetLocked(true);
		MasterSoundClass->Properties.Volume = 0;
	}
	else
	{
		MasterSoundVolumeSlider->SetLocked(false);
		MasterSoundClass->Properties.Volume = MasterSoundVolumeSlider->GetValue();
	}
}

void UPPSoundSettingWidget::ApplyBGMSoundToggle(bool IsChecked)
{
	if(IsChecked)
	{
		BGMSoundVolumeSlider->SetLocked(true);
		BGMSoundClass->Properties.Volume = 0;
	}
	else
	{
		BGMSoundVolumeSlider->SetLocked(false);
		BGMSoundClass->Properties.Volume = BGMSoundVolumeSlider->GetValue();
	}
}

void UPPSoundSettingWidget::ApplySFXSoundToggle(bool IsChecked)
{
	if(IsChecked)
	{
		SFXSoundVolumeSlider->SetLocked(true);
		SFXSoundClass->Properties.Volume = 0;
	}
	else
	{
		SFXSoundVolumeSlider->SetLocked(false);
		SFXSoundClass->Properties.Volume = SFXSoundVolumeSlider->GetValue();
	}
}