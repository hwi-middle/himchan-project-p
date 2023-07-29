// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PPLobbyUIBaseActor.h"
#include "PPSettingUIWidget.generated.h"

// 추후 PPVRPawn으로 옮길 예정
DECLARE_DELEGATE_OneParam(FLeftHandedSettingDelegate, bool IsChecked)
DECLARE_DELEGATE_OneParam(FControllerVibrationDelegate, bool IsChecked)
//

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
	FSettingButtonDelegate SettingButtonDelegate;
	void SaveSettingData();
	void LoadSettingData();
	// Generate Default Widget Section
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ExitSettingUI();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Button, meta = (BindWidget))
	TObjectPtr<UButton> ExitSettingUIButton;
	
	// Sound Option Function Section
	// UI 종류마다 함수를 하나로 통일하고 싶었는데...
	// 대충 찾아본 바로는 그렇게 하는거나 함수 여러개 만드는거나 가독성이나 복잡도는 비슷해보여서
	// 구현 편한 함수로 대체...
public:
	UFUNCTION(BlueprintCallable)
	void ApplyMasterSliderValue(float Value);

	UFUNCTION(BlueprintCallable)
	void ApplyBGMSliderValue(float Value);
	
	UFUNCTION(BlueprintCallable)
	void ApplySFXSliderValue(float Value);

	UFUNCTION(BlueprintCallable)
	void ApplyMasterSoundToggle(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyBGMSoundToggle(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplySFXSoundToggle(bool IsChecked);
	
	// Sound Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class USlider> MasterSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class USlider> BGMSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class USlider> SFXSoundVolumeSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class UCheckBox> MasterSoundToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class UCheckBox> BGMSoundToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound, meta = (BindWidget))
	TObjectPtr<class UCheckBox> SFXSoundToggle;

	// Display Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	void ApplyDisplayBrightnessSliderValue(float Value);
	
	UFUNCTION(BlueprintCallable)
	void ApplyDisplayVignettingSliderValue(float Value);
	
	// Display Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display, meta = (BindWidget))
	TObjectPtr<class USlider> DisplayBrightnessSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Display, meta = (BindWidget))
	TObjectPtr<class USlider> DisplayVignettingSlider;

	// Accessibility Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	void ApplyPauseInterfaceDistanceSliderValue(float Value);
	
	UFUNCTION(BlueprintCallable)
	void ApplyPauseInterfaceHeightSliderValue(float Value);

	UFUNCTION(BlueprintCallable)
	void ApplyLeftHandedSettingToggle(bool IsChecked);
	
	UFUNCTION(BlueprintCallable)
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
