// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPSettingUIWidget.generated.h"


/**
 * 
 */
UCLASS(meta =(DisableNativeTick))
class PROJECTP_API UPPSettingUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	// Base Widget Section
protected:
	virtual void NativeConstruct() override;

	// Sound Option Function Section
	// UI 종류마다 함수를 하나로 통일하고 싶었는데 
protected:
	void ApplyMasterSliderValue(float Value);
	void ApplyBgmSliderValue(float Value);
	void ApplySFXSliderValue(float Value);
	
	void ApplyMasterSoundToggle(bool IsChecked);
	void ApplyBgmSoundToggle(bool IsChecked);
	void ApplySFXSoundToggle(bool IsChecked);
	
	// Sound Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class USlider> MasterSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class USlider> BgmSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class USlider> SFXSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class UCheckBox> MasterSoundToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class UCheckBox> BgmSoundToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class UCheckBox> SFXSoundToggle;

	// Display Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display, meta = (BindWidget))
	TObjectPtr<class USlider> DisplayBrightnessSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display, meta = (BindWidget))
	TObjectPtr<class USlider> DisplayVignettingSlider;

	// Accessibility Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Accessibility, meta = (BindWidget))
	TObjectPtr<USlider> PauseInterfaceDistanceSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Accessibility, meta = (BindWidget))
	TObjectPtr<USlider> PauseInterfaceHeightSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Accessibility, meta = (BindWidget))
	TObjectPtr<UCheckBox> LeftHandedSettingToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Accessibility, meta = (BindWidget))
	TObjectPtr<UCheckBox> ControllerVibrationToggle;
};
