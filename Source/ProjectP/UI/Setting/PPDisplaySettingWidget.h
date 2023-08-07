// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "Blueprint/UserWidget.h"
#include "Engine/PostProcessVolume.h"
#include "ProjectP/Interface/SettingSubWidgetInterface.h"
#include "PPDisplaySettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPDisplaySettingWidget : public UUserWidget, public ISettingSubWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void SaveSettingData(UPPSaveSettingOption* SettingOption) override;
	virtual void LoadSettingData(UPPSaveSettingOption* SettingOption) override;
	
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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<APostProcessVolume> PostProcessVolume;
};
