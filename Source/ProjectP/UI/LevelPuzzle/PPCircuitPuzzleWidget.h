// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "PPCircuitPuzzleWidget.generated.h"

UENUM()
enum class ECircuitNum : uint8
{
	First,
	Second,
	Third
};

DECLARE_MULTICAST_DELEGATE(FCorrectCircuitDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FPassTargetCircuitDelegate, UButton* Button, ECircuitNum);
/**
 * 
 */

UCLASS()
class PROJECTP_API UPPCircuitPuzzleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	FORCEINLINE void AddWidgetWidthValue(const float Value) { SetPadding(FMargin(GetPadding().Left + Value, GetPadding().Top, GetPadding().Right + Value, GetPadding().Bottom)); }
	FORCEINLINE void SetWidgetWidthValue(const float Value) { SetPadding(FMargin(Value, GetPadding().Top, Value, GetPadding().Bottom)); }
	FORCEINLINE float GetWidgetWidthValue() { return GetPadding().Left; }

	FORCEINLINE void SetEnableTexture() {EndPointImage->SetBrushFromTexture(EnableTexture); }
	
	FCorrectCircuitDelegate CorrectCircuitDelegate;
	FPassTargetCircuitDelegate PassTargetCircuitDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> StartPointImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> EndPointImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> FirstCircuit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> SecondCircuit;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ThirdCircuit;

private:
	UFUNCTION()
	FORCEINLINE void PassFirstCircuitWidget()
	{
		PassTargetCircuitDelegate.Broadcast(FirstCircuit, ECircuitNum::First);
	}
	
	UFUNCTION()
	FORCEINLINE void PassSecondCircuitWidget()
	{
		PassTargetCircuitDelegate.Broadcast(SecondCircuit, ECircuitNum::Second);
	}
	
	UFUNCTION()
	FORCEINLINE void PassThirdCircuitWidget()
	{
		PassTargetCircuitDelegate.Broadcast(ThirdCircuit, ECircuitNum::Third);
	}
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> EnableTexture;
	
};
