// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "ProjectP/Enumeration/PPSubWidgetType.h"
#include "ProjectP/UI/Setting/PPSoundSettingWidget.h"
#include "ProjectP/UI/Setting/PPGraphicSettingWidget.h"
#include "ProjectP/UI/Setting/PPDisplaySettingWidget.h"
#include "ProjectP/UI/Setting/PPSubtitleSettingWidget.h"
#include "ProjectP/UI/Setting/PPAccessibilitySettingWidget.h"
#include "PPSettingUIWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FLoadMainWidgetDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FPassSubWidgetTypeDelegate, ESubWidgetType);
/*
 * 
 */
UCLASS(meta =(DisableNativeTick))
class PROJECTP_API UPPSettingUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SaveSettingData();
	void LoadSettingData();
	
	FORCEINLINE void AddSubWidgetHeightOffset(const float Height) { SubWidgetPanelSlot->SetOffsets(FMargin(SubWidgetPanelSlot->GetOffsets().Left, SubWidgetPanelSlot->GetOffsets().Top + Height, SubWidgetPanelSlot->GetOffsets().Right, SubWidgetPanelSlot->GetOffsets().Bottom + Height)); }
	
	FORCEINLINE void SetSubWidgetHeightOffset(const float Height) { SubWidgetPanelSlot->SetOffsets(FMargin(SubWidgetPanelSlot->GetOffsets().Left, Height, SubWidgetPanelSlot->GetOffsets().Right, Height)); }
	
	FORCEINLINE float GetSubWidgetHeight() const { return SubWidgetPanelSlot->GetOffsets().Top; }

	void SetSubWidgetContent(ESubWidgetType SubWidget);
	void SetSubWidgetContentVisible(const bool IsActivate);
	FORCEINLINE void SetSubWidgetPanelVisible(const bool Visible) { Visible == true ? SubWidgetPanel->SetRenderOpacity(1.0f) : SubWidgetPanel->SetRenderOpacity(0.0f); }
	FORCEINLINE void SetSubWidgetAnimationWorking(const bool Work) { Work == true? bSubWidgetAnimationWork = true : bSubWidgetAnimationWork = false; }
	
	FLoadMainWidgetDelegate LoadMainWidgetDelegate;
	FPassSubWidgetTypeDelegate PassSubWidgetTypeDelegate;
	
	// Widget Animation
protected:
	UFUNCTION(BlueprintCallable)
	void ActivateSoundSettingWidget();

	UFUNCTION(BlueprintCallable)
	void ActivateDisplaySettingWidget();

	UFUNCTION(BlueprintCallable)
	void ActivateGraphicSettingWidget();

	UFUNCTION(BlueprintCallable)
	void ActivateAccessibilitySettingWidget();

	UFUNCTION(BlueprintCallable)
	void ActivateSubtitleSettingWidget();
	
	// Default Widget Section
protected:

	UFUNCTION(BlueprintCallable)
	void ExitSettingUI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> SettingPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> SubWidgetPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> OpenSoundSettingWidgetButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> OpenDisplaySettingWidgetButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> OpenGraphicSettingWidgetButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> OpenAccessibilitySettingWidgetButton;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> OpenSubtitleSettingWidgetButton;
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ExitSettingUIButton;
	
	// SubWidgets;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UCanvasPanelSlot> SubWidgetPanelSlot; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UPPSoundSettingWidget> SoundSettingWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UPPDisplaySettingWidget> DisplaySettingWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UPPGraphicSettingWidget> GraphicSettingWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UPPAccessibilitySettingWidget> AccessibilitySettingWidget;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UPPSubtitleSettingWidget> SubtitleSettingWidget;
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUserWidget> EnabledSubWidget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	uint32 bSubWidgetAnimationWork : 1;
	
	UPROPERTY()
	ESubWidgetType EnabledSubWidgetType;
};
