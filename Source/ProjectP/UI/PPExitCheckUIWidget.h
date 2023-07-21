// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPExitCheckUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPExitCheckUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	virtual void NativeConstruct() override;
};
