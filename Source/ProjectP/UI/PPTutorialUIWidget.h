// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectP/Enumeration/PPWidgetName.h"
#include "PPTutorialUIWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FTutorialButtonDelegate, EWidgetName);

/**
 * 
 */
UCLASS(meta =(DisableNativeTick))
class PROJECTP_API UPPTutorialUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FTutorialButtonDelegate TutorialButtonDelegate;
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Button, meta = (BindWidget))
	TObjectPtr<UButton> ExitSettingUIButton;
	
};
