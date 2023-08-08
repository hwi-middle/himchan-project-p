// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Engine/PostProcessVolume.h"
#include "ProjectP/Enumeration/PPWidgetType.h"
#include "PPSettingUIWidget.generated.h"

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
	
	// Default Widget Section
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ExitSettingUI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ExitSettingUIButton;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> SelectSettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> SoundSettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> DisplaySettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> GraphicSettingPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UGridPanel> AccessibilitySettingPanel;
	*/
	UPROPERTY()
	uint32 bSubWidgetOpened : 1;
};
