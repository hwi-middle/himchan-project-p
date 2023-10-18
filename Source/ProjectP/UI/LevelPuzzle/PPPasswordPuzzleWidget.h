// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PPPasswordPuzzleWidget.generated.h"

/*
  ___  ______  _   __ _   _  _____  _____  _   _  _____ 
 / _ \ | ___ \| | / /| \ | ||_   _||  __ \| | | ||_   _|
/ /_\ \| |_/ /| |/ / |  \| |  | |  | |  \/| |_| |  | |  
|  _  ||    / |    \ | . ` |  | |  | | __ |  _  |  | |  
| | | || |\ \ | |\  \| |\  | _| |_ | |_\ \| | | |  | |  
\_| |_/\_| \_|\_| \_/\_| \_/ \___/  \____/\_| |_/  \_/  
																										
 */
DECLARE_MULTICAST_DELEGATE(FCorrectPasswordDelegate);

/**
 * 
 */

UENUM()
enum EPasswordPuzzleButton
{
	Num0,
	Num1,
	Num2,
	Num3,
	Num4,
	Num5,
	Num6,
	Num7,
	Num8,
	Num9,
	Delete,
	Confirm,
	MAX_COUNT,
};
UCLASS()
class PROJECTP_API UPPPasswordPuzzleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	FORCEINLINE void AddWidgetWidthValue(const float Value) { SetPadding(FMargin(GetPadding().Left + Value, GetPadding().Top, GetPadding().Right + Value, GetPadding().Bottom)); }
	FORCEINLINE void SetWidgetWidthValue(const float Value) { SetPadding(FMargin(Value, GetPadding().Top, Value, GetPadding().Bottom)); }
	FORCEINLINE float GetWidgetWidthValue() { return GetPadding().Left; }
	
	FORCEINLINE void SetCorrectPassword(FString Password) { CorrectPassword = Password; GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, Password);}
	
	FCorrectPasswordDelegate CorrectPasswordDelegate;

protected:
	UPROPERTY()
	TArray<UButton*> ButtonArray;

	UPROPERTY()
	TArray<UTextBlock*> PasswordDigitArray;
	
	UPROPERTY()
	uint32 CurrentDigit;

	UPROPERTY()
	uint32 MaxDigit;

	UPROPERTY()
	FString CorrectPassword;
	
private:
	void PerformButtonInteraction(const EPasswordPuzzleButton InButton);
	void AppendPasswordDigit(uint32 InDigit);
	void DeletePasswordDigit();
	void CheckCorrectPasswordDigit();
	
	UFUNCTION()
	FORCEINLINE void OnPressNum0() { PerformButtonInteraction(EPasswordPuzzleButton::Num0); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum1() { PerformButtonInteraction(EPasswordPuzzleButton::Num1); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum2() { PerformButtonInteraction(EPasswordPuzzleButton::Num2); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum3() { PerformButtonInteraction(EPasswordPuzzleButton::Num3); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum4() { PerformButtonInteraction(EPasswordPuzzleButton::Num4); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum5() { PerformButtonInteraction(EPasswordPuzzleButton::Num5); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum6() { PerformButtonInteraction(EPasswordPuzzleButton::Num6); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum7() { PerformButtonInteraction(EPasswordPuzzleButton::Num7); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum8() { PerformButtonInteraction(EPasswordPuzzleButton::Num8); }
	
	UFUNCTION()
	FORCEINLINE void OnPressNum9() { PerformButtonInteraction(EPasswordPuzzleButton::Num9); }
	
	UFUNCTION()
	FORCEINLINE void OnPressDelete() { PerformButtonInteraction(EPasswordPuzzleButton::Delete); }
	
	UFUNCTION()
	FORCEINLINE void OnPressConfirm() { PerformButtonInteraction(EPasswordPuzzleButton::Confirm); }
	
public:
	FORCEINLINE UButton* GetButtonByIndex(const EPasswordPuzzleButton InButton) { return ButtonArray[InButton]; }
};
