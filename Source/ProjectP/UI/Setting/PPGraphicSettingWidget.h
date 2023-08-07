// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "ProjectP/Interface/SettingSubWidgetInterface.h"
#include "PPGraphicSettingWidget.generated.h"

UENUM()
enum class EGraphicQuality : uint8
{
	Low = 0,
	Middle = 1,
	High = 2,
};

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPGraphicSettingWidget : public UUserWidget, public ISettingSubWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void LoadSettingData(UPPSaveSettingOption* SettingOption) override;
	virtual void SaveSettingData(UPPSaveSettingOption* SettingOption) override;

public:
	UFUNCTION(BlueprintCallable)
	void ApplyTextureQualityLow(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyTextureQualityMiddle(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyTextureQualityHigh(bool IsChecked);
	
	UFUNCTION(BlueprintCallable)
	void ApplyShadowQualityLow(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyShadowQualityMiddle(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyShadowQualityHigh(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyAAQualityLow(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyAAQualityMiddle(bool IsChecked);

	UFUNCTION(BlueprintCallable)
	void ApplyAAQualityHigh(bool IsChecked);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> TextureQualityLowButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> TextureQualityMiddleButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> TextureQualityHighButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> ShadowQualityLowButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> ShadowQualityMiddleButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> ShadowQualityHighButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> AAQualityLowButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> AAQualityMiddleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> AAQualityHighButton;

};
