// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
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

	FORCEINLINE void SetPanelOpacity(const float Opacity) { TutorialPanel->SetRenderOpacity(Opacity); }
	FORCEINLINE float GetPanelOpacity() const { return TutorialPanel->GetRenderOpacity(); }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> TutorialPanel;
	
};
