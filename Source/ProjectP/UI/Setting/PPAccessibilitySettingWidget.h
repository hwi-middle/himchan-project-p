// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "ProjectP/Interface/SettingSubWidgetInterface.h"
#include "PPAccessibilitySettingWidget.generated.h"

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

// VRPawn 작업 끝난 뒤에 VRPawn에 함수 만들어서 아래 두 델리게이트에 바인딩 할 예정
DECLARE_MULTICAST_DELEGATE_OneParam(FCameraTurnValueSettingDelegate, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAccessibilityOptionDelegate, EAccessibilityOption, bool);

/**
 * 
 */

UCLASS()
class PROJECTP_API UPPAccessibilitySettingWidget : public UUserWidget, public ISettingSubWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void SaveSettingData(UPPSaveSettingOption* SettingOption) override;
	virtual void LoadSettingData(UPPSaveSettingOption* SettingOption) override;

	FCameraTurnValueSettingDelegate CameraTurnValueSettingDelegate;
	FAccessibilityOptionDelegate AccessibilityOptionDelegate;
	
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
