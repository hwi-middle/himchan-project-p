// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PPEndingUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPEndingUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	FORCEINLINE void SetScreenImage(const uint32 ArrayNum) { ScreenImage->SetBrushFromTexture(ScreenImageArray[ArrayNum]); }
	// Variable Section
protected:
	UPROPERTY(EditDefaultsOnly, Category = Images)
	TArray<UTexture2D*> ScreenImageArray;
	
	// Widget Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ScreenImage;
	
};
