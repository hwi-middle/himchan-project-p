// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PPTutorialUIWidget.generated.h"

/**
 * 
 */
UCLASS(meta = (DisableNativeTick))
class PROJECTP_API UPPTutorialUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	FORCEINLINE void SetBackgroundOpacity(const float Opacity) { BackgroundImage->SetRenderOpacity(Opacity); }
	FORCEINLINE float GetBackgroundOpacity() const { return BackgroundImage->GetRenderOpacity(); }

	FORCEINLINE void AddWidgetWidthValue(const float Value) { SetPadding(FMargin(GetPadding().Left + Value, GetPadding().Top, GetPadding().Right + Value, GetPadding().Bottom)); }
	FORCEINLINE float GetWidgetWidthValue() { return GetPadding().Left; }
	
	FORCEINLINE void SetGuidePanelOpacity(const float Opacity) { GuidePanel->SetRenderOpacity(Opacity); }
	FORCEINLINE float GetGuidePanelOpacity() const { return GuidePanel->GetRenderOpacity(); }
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> GuidePanel;
};


