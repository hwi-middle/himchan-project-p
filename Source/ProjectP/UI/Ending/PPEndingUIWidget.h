// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "PPEndingUIWidget.generated.h"

/**
 * 
 */
UCLASS(meta = (DisableNativeTick))
class PROJECTP_API UPPEndingUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	bool SetScreenImage(const uint32 ArrayNum);
	FORCEINLINE uint32 GetCurrentScreenImageNum() const { return CurrentImageNum; }
	FORCEINLINE void SetEndingText(const FText Text) const { EndingText->SetText(Text); }
	FORCEINLINE void SetScreenOpacity(const float Opacity) { ScreenImage->SetRenderOpacity(Opacity); }
	FORCEINLINE float GetScreenOpacity() const { return ScreenImage->GetRenderOpacity(); }

	FORCEINLINE void SetCreditOpacity(const float Opacity) { CreditPanel->SetRenderOpacity(Opacity); }
	FORCEINLINE float GetCreditOpacity() const { return CreditPanel->GetRenderOpacity(); }
	FORCEINLINE float GetCreditHeight() const { return CreditPanelSlot->GetSize().Y; }
	float AddCreditPosition(const float AddPosY);
	
	// Variable Section
protected:
	UPROPERTY(EditDefaultsOnly, Category = Images)
	TArray<UTexture2D*> ScreenImageArray;
	
	// Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScreenImage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> EndingText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CreditPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCanvasPanelSlot> CreditPanelSlot;
	
	UPROPERTY()
	uint32 CurrentImageNum;
};
