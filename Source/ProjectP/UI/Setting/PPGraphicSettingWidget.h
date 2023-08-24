// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ProjectP/Interface/SettingSubWidgetInterface.h"
#include "PPGraphicSettingWidget.generated.h"

UENUM()
enum class EAAType : uint8
{
	FXAA = 1,
	TAA = 2
};

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
	virtual void SaveSettingData(UPPSaveSettingOption* SettingOption) override;
	virtual void LoadSettingData(UPPSaveSettingOption* SettingOption) override;

public:
	UFUNCTION(BlueprintCallable)
	void ApplyTextureQualityLow();

	UFUNCTION(BlueprintCallable)
	void ApplyTextureQualityMiddle();

	UFUNCTION(BlueprintCallable)
	void ApplyTextureQualityHigh();
	
	UFUNCTION(BlueprintCallable)
	void ApplyShadowQualityLow();

	UFUNCTION(BlueprintCallable)
	void ApplyShadowQualityMiddle();

	UFUNCTION(BlueprintCallable)
	void ApplyShadowQualityHigh();

	UFUNCTION(BlueprintCallable)
	void SetCurrenAAToFXAA();

	UFUNCTION(BlueprintCallable)
	void SetCurrenAAToTAA();
	
	UFUNCTION(BlueprintCallable)
	void ApplyAAQualityLow();

	UFUNCTION(BlueprintCallable)
	void ApplyAAQualityMiddle();

	UFUNCTION(BlueprintCallable)
	void ApplyAAQualityHigh();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> TextureQualityLowButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> TextureQualityMiddleButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> TextureQualityHighButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ShadowQualityLowButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ShadowQualityMiddleButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ShadowQualityHighButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> EnableFXAAButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> EnableTAAButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> AAQualityLowButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> AAQualityMiddleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> AAQualityHighButton;

	// 텍스트 색 바꾸러면 생노가다를 해야하네 끼에에엑
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> TQLowText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> TQMiddleText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> TQHighText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> SQLowText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> SQMiddleText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> SQHighText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> FXAAText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> TAAText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> AALowText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> AAMiddleText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> AAHighText;
};
