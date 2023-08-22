// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Enumeration/PPSubWidgetType.h"
#include "PPLobbyUIWidget.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FPassSubWidgetTypeDelegate, ESubWidgetType);
DECLARE_MULTICAST_DELEGATE(FStartGameDelegate);
/**
 * 
 */
UCLASS()
class PROJECTP_API UPPLobbyUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void AddWidgetHeightOffset(const float Height) { WidgetPanelSlot->SetOffsets(FMargin(WidgetPanelSlot->GetOffsets().Left, WidgetPanelSlot->GetOffsets().Top + Height, WidgetPanelSlot->GetOffsets().Right, WidgetPanelSlot->GetOffsets().Bottom + Height)); }

	FORCEINLINE void SetWidgetHeightOffset(const float Height) { WidgetPanelSlot->SetOffsets(FMargin(WidgetPanelSlot->GetOffsets().Left, Height, WidgetPanelSlot->GetOffsets().Right, Height)); }

	FORCEINLINE float GetSubWidgetHeight() const { return WidgetPanelSlot->GetOffsets().Top; }
	
	void SetButtonInteraction(bool bInteraction);
	
	FPassSubWidgetTypeDelegate PassSubWidgetTypeDelegate;
	
	FStartGameDelegate StartGameDelegate;
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void EntryMainLevel();
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ActivateSettingWidget() { PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Setting); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ActivateExitWidget() { PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Exit); }
	
	// Widget
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UCanvasPanel> WidgetPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UCanvasPanelSlot> WidgetPanelSlot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UButton> StartButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UButton> SettingButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UButton> ExitButton;
};
