// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ProjectP/Util/StringDataTable.h"
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
	
	FORCEINLINE void SetTutorialPanelOpacity(const float Opacity) { TutorialPanel->SetRenderOpacity(Opacity); }
	FORCEINLINE float GetTutorialPanelOpacity() const { return TutorialPanel->GetRenderOpacity(); }

	FORCEINLINE void SetTutorialImage(UTexture2D* Image) const { TutorialImage->SetBrushFromTexture(Image); }
	FORCEINLINE void SetTitleText(const FString TitleString) const { TutorialTitleTextBlock->SetText(FText::FromString(TitleString)); }
	FORCEINLINE void SetInfoText(const FString InfoString) const { TutorialInfoTextBlock->SetText(FText::FromString(InfoString)); }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> TutorialPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> TutorialImage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TutorialTitleTextBlock;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TutorialInfoTextBlock; 
	
};


