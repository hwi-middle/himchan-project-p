// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PPSaveSettingOption.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPSaveSettingOption : public USaveGame
{
	GENERATED_BODY()
public:
	UPPSaveSettingOption();

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	FString SaveFileName;

	// SoundOption
public:
	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float MasterSoundVolumeSliderValue;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float BGMSoundVolumeSliderValue;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float SFXSoundVolumeSliderValue;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 bMasterSoundToggle : 1;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 bBGMSoundToggle : 1;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 bSFXSoundToggle : 1;

	// DisplayOption
public:
	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float DisplayBrightnessValue;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float DisplayVignettingValue;

	// GraphicOption
public:
	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 TextureQualityValue;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 ShadowQualityValue;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 AAType;
	
	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 AAQualityValue;
	
	// AccessibilityOption
public:
	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float PauseInterfaceDistanceValue;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float PauseInterfaceHeightValue;
	
	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 bUseLeftHandedSetting : 1;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	uint32 bUseControllerVibration : 1;

	UPROPERTY(EditDefaultsOnly, Category = SettingOption)
	float CameraTurnValue;
};
