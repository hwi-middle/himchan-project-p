// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPSettingUIWidget.generated.h"

DECLARE_DELEGATE_OneParam(FLeftHandedSettingDelegate, bool IsChecked)
DECLARE_DELEGATE_OneParam(FControllerVibrationDelegate, bool IsChecked)

/*
 * 
 */
UCLASS(meta =(DisableNativeTick))
class PROJECTP_API UPPSettingUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FLeftHandedSettingDelegate LeftHandedSettingDelegate;
	FControllerVibrationDelegate ControllerVibrationDelegate;
	// Base Widget Section
protected:
	virtual void NativeConstruct() override;

	// Sound Option Function Section
	// UI 종류마다 함수를 하나로 통일하고 싶었는데...
	// 대충 찾아본 바로는 그렇게 하는거나 함수 여러개 만드는거나 가독성이나 복잡도는 비슷해보여서
	// 구현 편한 함수로 대체...
public:
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

	// Display Option Function Section
public:
	void ApplyDisplayBrightnessSliderValue(float Value);
	void ApplyDisplayVignettingSliderValue(float Value);
	
	// Display Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display, meta = (BindWidget))
	TObjectPtr<class USlider> DisplayBrightnessSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display, meta = (BindWidget))
	TObjectPtr<class USlider> DisplayVignettingSlider;

	// Accessibility Option Function Section
public:
	void ApplyPauseInterfaceDistanceSliderValue(float Value);
	void ApplyPauseInterfaceHeightSliderValue(float Value);
	
	void ApplyLeftHandedSettingToggle(bool IsChecked);
	void ApplyControllerVibrationToggle(bool IsChecked);
	
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
