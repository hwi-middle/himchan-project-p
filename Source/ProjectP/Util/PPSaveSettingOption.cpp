// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Util/PPSaveSettingOption.h"

UPPSaveSettingOption::UPPSaveSettingOption()
{
	MasterSoundVolumeSliderValue = 50.0f;
	BgmSoundVolumeSliderValue = 50.0f;
	SFXSoundVolumeSliderValue = 50.f;
	DisplayBrightnessValue = 0.5f;
	DisplayVignettingValue = 0.0f;
	PauseInterfaceDistanceValue = 0.5f;
	PauseInterfaceHeightValue = 0.5f;
	bUseLeftHandedSetting = false;
	bUseControllerVibration = true;
}
