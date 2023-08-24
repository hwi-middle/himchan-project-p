// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/RadialSlider.h"
#include "PPVitalWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPVitalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetVitalImageScale(const float Scale) { VitalImage->SetRenderScale(FVector2d(Scale, Scale)); }
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// widget
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<URadialSlider> VitalRadialSlider;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta=(BindWidget))
	TObjectPtr<UImage> VitalImage;
	
private:
	UPROPERTY()
	TObjectPtr<class APPCharacterPlayer> PlayerCharacter;

	UPROPERTY()
	float PlayerMaximumHealth;
	
	UPROPERTY()
	float PlayerCurrentHealth;

	UPROPERTY()
	float ImageMaximumScale;

	UPROPERTY()
	float ImageMinimumScale;
	
	FVector2d ImageScalingValue;
	
	UPROPERTY()
	uint32 bIsUpScaling : 1;
};
