// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPSettingUIWidget.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTP_API UPPSettingUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
protected:
	virtual void NativeConstruct() override;
};
