// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Engine/Font.h"
#include "PPSubtitleSettingUIWidget.generated.h"

UENUM()
enum class ESubtitleFontSize : uint8
{
	Small = 32,
	Normal = 48,
	Large = 60
};

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPSubtitleSettingUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:

protected:
	virtual void NativeConstruct() override;
	
	// Subtitle Option Function Section
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplySubtitleFontSizeSmall() { check(GEngine); GEngine->GetSubtitleFont()->LegacyFontSize = StaticCast<uint32>(ESubtitleFontSize::Small); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplySubtitleFontSizeNormal() { check(GEngine); GEngine->GetSubtitleFont()->LegacyFontSize = StaticCast<uint32>(ESubtitleFontSize::Normal); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ApplySubtitleFontSizeLarge() { check(GEngine); GEngine->GetSubtitleFont()->LegacyFontSize = StaticCast<uint32>(ESubtitleFontSize::Large); }
	// Subtitle Option Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCheckBox> SubtitleToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> SubtitleSmallFontSizeButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> SubtitleNormalFontSizeButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> SubtitleLargeFontSizeButton;
};
