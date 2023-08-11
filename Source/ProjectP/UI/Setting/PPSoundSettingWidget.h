// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundClass.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"
#include "Blueprint/UserWidget.h"
#include "ProjectP/Interface/SettingSubWidgetInterface.h"
#include "PPSoundSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPSoundSettingWidget : public UUserWidget, public ISettingSubWidgetInterface
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void SaveSettingData(UPPSaveSettingOption* SettingOption) override;
	virtual void LoadSettingData(UPPSaveSettingOption* SettingOption) override;
	
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
};
