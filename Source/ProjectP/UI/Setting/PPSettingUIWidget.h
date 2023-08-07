// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Engine/PostProcessVolume.h"
#include "ProjectP/Enumeration/PPWidgetType.h"
#include "Sound/SoundClass.h"
#include "PPSettingUIWidget.generated.h"

UENUM()
enum class ECameraTurnValue : uint8
{
	Low = 30,
	Middle = 45,
	High = 60
};

UENUM()
enum class EAccessibilityOption : uint8
{
	LeftHanded,
	Vibration,
	CameraTurn
};

DECLARE_MULTICAST_DELEGATE_OneParam(FSettingButtonDelegate, EWidgetType);
// VRPawn 작업 끝난 뒤에 VRPawn에 함수 만들어서 아래 두 델리게이트에 바인딩 할 예정
DECLARE_MULTICAST_DELEGATE_OneParam(FCameraTurnValueSettingDelegate, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAccessibilityOptionDelegate, EAccessibilityOption, bool);

/*
 * 
 */
UCLASS(meta =(DisableNativeTick))
class PROJECTP_API UPPSettingUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SaveSettingData();
	void LoadSettingData();

	FSettingButtonDelegate SettingButtonDelegate;
	FCameraTurnValueSettingDelegate CameraTurnValueSettingDelegate;
	FAccessibilityOptionDelegate AccessibilityOptionDelegate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<APostProcessVolume> PostProcessVolume;
	// Default Widget Section
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ExitSettingUI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ExitSettingUIButton;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> SelectSettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> SoundSettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> DisplaySettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> GraphicSettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> AccessibilitySettingPanel;
	*/
	UPROPERTY()
	uint32 bSubWidgetOpened : 1;
	
	// Sound Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyMasterSliderValue(const float Value) { MasterSoundClass->Properties.Volume = Value; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyBGMSliderValue(const float Value) { BGMSoundClass->Properties.Volume = Value; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplySFXSliderValue(const float Value) { SFXSoundClass->Properties.Volume = Value; }

	UFUNCTION(BlueprintCallable)
	void ApplyMasterSoundToggle(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyBGMSoundToggle(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplySFXSoundToggle(bool IsChecked);
	
	// Sound Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class USlider> MasterSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class USlider> BGMSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class USlider> SFXSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UCheckBox> MasterSoundToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UCheckBox> BGMSoundToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UCheckBox> SFXSoundToggle;

	// Sound Class Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SoundClass")
	TObjectPtr<class USoundClass> MasterSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SoundClass")
	TObjectPtr<class USoundClass> BGMSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SoundClass")
	TObjectPtr<class USoundClass> SFXSoundClass;
	
	// Display Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyDisplayBrightnessSliderValue(const float Value) {  PostProcessVolume->Settings.AutoExposureBias = Value; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyDisplayVignettingSliderValue(const float Value) { PostProcessVolume->Settings.VignetteIntensity = Value; }
	
	// Display Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class USlider> DisplayBrightnessSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class USlider> DisplayVignettingSlider;

	// Accessibility Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	void ApplyPauseInterfaceDistanceSliderValue(float Value);
	
	UFUNCTION(BlueprintCallable)
	void ApplyPauseInterfaceHeightSliderValue(float Value);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyLeftHandedSettingToggle(const bool IsChecked) { AccessibilityOptionDelegate.Broadcast(EAccessibilityOption::LeftHanded, IsChecked); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyControllerVibrationToggle(const bool IsChecked) { AccessibilityOptionDelegate.Broadcast(EAccessibilityOption::Vibration, IsChecked); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyCameraTurnValueLow() { CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Low)); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyCameraTurnValueMiddle() { CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Middle)); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyCameraTurnValueHigh() { CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::High)); }
	
	// Accessibility Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<USlider> PauseInterfaceDistanceSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<USlider> PauseInterfaceHeightSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> LeftHandedSettingToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> ControllerVibrationToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI"/*, *meta = (BindWidget)*/)
	TObjectPtr<UButton> CameraTurnValueLowButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI"/*, *meta = (BindWidget)*/)
	TObjectPtr<UButton> CameraTurnValueMiddleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI"/*, *meta = (BindWidget)*/)
	TObjectPtr<UButton> CameraTurnValueHighButton;
};
