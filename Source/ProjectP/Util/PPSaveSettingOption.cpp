// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Util/PPSaveSettingOption.h"

UPPSaveSettingOption::UPPSaveSettingOption()
{
	SaveFileName = "SettingOptionsData";
	MasterSoundVolumeSliderValue = 0.5f;
	BGMSoundVolumeSliderValue = 0.5f;
	SFXSoundVolumeSliderValue = 0.5f;
	bMasterSoundToggle = false;
	bBGMSoundToggle = false;
	bSFXSoundToggle = false;
	DisplayBrightnessValue = 0.5f;
	DisplayVignettingValue = 0.0f;
	TextureQualityValue = 2;
	ShadowQualityValue = 2;
	AAQualityValue = 2;
	PauseInterfaceDistanceValue = 0.5f;
	PauseInterfaceHeightValue = 0.5f;
	bUseLeftHandedSetting = false;
	bUseControllerVibration = true;
}
