// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Engine/Font.h"
#include "ProjectP/Interface/SettingSubWidgetInterface.h"
#include "PPSubtitleSettingWidget.generated.h"

UENUM()
enum class ESubtitleFontSize : uint8
{
	Small = 32,
	Normal = 48,
	Large = 60
};

/**
 * 자막 관련 기능은 잠시 구현 중단. VR 자막이 시각적으로 불편함을 유발할 경우 폐기함.
 */
UCLASS()
class PROJECTP_API UPPSubtitleSettingWidget : public UUserWidget, public ISettingSubWidgetInterface
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void SaveSettingData(UPPSaveSettingOption* SettingOption) override;
	virtual void LoadSettingData(UPPSaveSettingOption* SettingOption) override;
	
	// Subtitle Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	void ApplySubtitleFontSizeSmall(const bool IsChecked);
	UFUNCTION(BlueprintCallable)
	void ApplySubtitleFontSizeNormal(const bool IsChecked);
	UFUNCTION(BlueprintCallable)
	void ApplySubtitleFontSizeLarge(const bool IsChecked);

protected:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//TObjectPtr<PPVRSubtitleActor> VRSubtitle;
	
	// Subtitle Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> SubtitleToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> SubtitleSmallFontSizeButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> SubtitleNormalFontSizeButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> SubtitleLargeFontSizeButton;
};
