// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "ProjectP/Interface/SettingSubWidgetInterface.h"
#include "PPAccessibilitySettingWidget.generated.h"

UENUM()
enum class ECameraTurnValue : uint8
{
	Low = 30,
	Middle = 45,
	High = 60
};

// VRPawn 작업 끝난 뒤에 VRPawn에 함수 만들어서 아래 두 델리게이트에 바인딩 할 예정
DECLARE_MULTICAST_DELEGATE_OneParam(FCameraTurnValueSettingDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FVibrationOptionDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FLeftHandedOptionDelegate, bool);

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
	FVibrationOptionDelegate VibrationOptionDelegate;
	FLeftHandedOptionDelegate LeftHandedOptionDelegate;
	
	// Accessibility Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	void ApplyPauseInterfaceDistanceSliderValue(float Value);
	
	UFUNCTION(BlueprintCallable)
	void ApplyPauseInterfaceHeightSliderValue(float Value);

	UFUNCTION(BlueprintCallable)
	void ApplyLeftHandedSetting(const bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyRightHandedSetting(const bool IsChecked);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyControllerVibrationToggle(const bool IsChecked) { VibrationOptionDelegate.Broadcast(IsChecked); }

	UFUNCTION(BlueprintCallable)
	void ApplyCameraTurnValueLow(const bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyCameraTurnValueMiddle(const bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyCameraTurnValueHigh(const bool IsChecked);
	
	// Accessibility Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<USlider> PauseInterfaceDistanceSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<USlider> PauseInterfaceHeightSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> LeftHandedSettingButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> RightHandedSettingButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> ControllerVibrationToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> CameraTurnValueLowButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> CameraTurnValueMiddleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> CameraTurnValueHighButton;

protected:
	UPROPERTY()
	float NewCameraTurnValue;
};
