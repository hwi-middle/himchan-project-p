// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Engine/PostProcessVolume.h"
#include "ProjectP/Enumeration/PPWidgetType.h"
#include "Sound/SoundClass.h"
#include "PPSettingUIWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FSettingButtonDelegate, EWidgetType);
// VRPawn 작업 끝난 뒤에 VRPawn에 함수 만들어서 아래 두 델리게이트에 바인딩 할 예정
DECLARE_MULTICAST_DELEGATE_OneParam(FCameraTurnValueSettingDelegate, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAccessibilityOptionDelegate, FName, bool);

UENUM()
enum class ECameraTurnValue : uint8
{
	Low = 30,
	Middle = 45,
	High = 60
};

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<APostProcessVolume> PostProcessVolume;
	// Generate Default Widget Section
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ExitSettingUI();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Button, meta = (BindWidget))
	TObjectPtr<UButton> ExitSettingUIButton;

	/*
	 * Sound Option Function Section
	 * UI 종류마다 함수를 하나로 통일하고 싶었는데...
	 * 대충 찾아본 바로는 그렇게 하는거나 함수 여러개 만드는거나 가독성이나 복잡도는 비슷해보여서
	 * (Template Class랑 Enum 만들고 바인딩 할 '때' 마다 람다식 만들어야 함)
	 * https://forums.unrealengine.com/t/dynamic-multicast-delegate-how-to-bind-lambda/140046/13
	 * (또는 엔진 내 UMG Delegate 뜯어 고치는건데 프로젝트 관리에 매우 좋지 못함)
	 * 구현 편한 함수 여러개 선언하는 방식으로 대체. 어쩌피 여기말곤 쓰는 곳도 없어서 오히려 공수만 들고 작업속도 지연될것 같기도
	*/
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

	// Sound Class Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SoundClass)
	TObjectPtr<class USoundClass> MasterSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SoundClass)
	TObjectPtr<class USoundClass> BGMSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SoundClass)
	TObjectPtr<class USoundClass> SFXSoundClass;
	
	// Display Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyDisplayBrightnessSliderValue(const float Value) {  PostProcessVolume->Settings.AutoExposureBias = Value; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyDisplayVignettingSliderValue(const float Value) { PostProcessVolume->Settings.VignetteIntensity = Value; }
	
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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyCameraTurnValueLow() { CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Low)); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyCameraTurnValueMiddle() { CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Middle)); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplyCameraTurnValueHigh() { CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::High)); }
	
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Accessibility/*, *meta = (BindWidget)*/)
	TObjectPtr<UButton> CameraTurnValueLowButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Accessibility/*, *meta = (BindWidget)*/)
	TObjectPtr<UButton> CameraTurnValueMiddleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Accessibility/*, *meta = (BindWidget)*/)
	TObjectPtr<UButton> CameraTurnValueHighButton;
};
