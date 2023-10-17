// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PPPasswordPuzzleWidget.generated.h"

class UTextBlock;
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
protected:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY()
	TArray<UButton*> ButtonArray;

	UPROPERTY()
	TArray<UTextBlock*> PasswordDigitArray;
	
	UPROPERTY()
	uint32 CurrentDigit;

	UPROPERTY()
	uint32 MaxDigit;

private:
	void PerformButtonInteraction(const EPasswordPuzzleButton InButton);
	void AppendPasswordDigit(uint32 InDigit);
	void DeletePasswordDigit();
	FORCEINLINE void OnPressNum0() { PerformButtonInteraction(EPasswordPuzzleButton::Num0); }
	FORCEINLINE void OnPressNum1() { PerformButtonInteraction(EPasswordPuzzleButton::Num1); }
	FORCEINLINE void OnPressNum2() { PerformButtonInteraction(EPasswordPuzzleButton::Num2); }
	FORCEINLINE void OnPressNum3() { PerformButtonInteraction(EPasswordPuzzleButton::Num3); }
	FORCEINLINE void OnPressNum4() { PerformButtonInteraction(EPasswordPuzzleButton::Num4); }
	FORCEINLINE void OnPressNum5() { PerformButtonInteraction(EPasswordPuzzleButton::Num5); }
	FORCEINLINE void OnPressNum6() { PerformButtonInteraction(EPasswordPuzzleButton::Num6); }
	FORCEINLINE void OnPressNum7() { PerformButtonInteraction(EPasswordPuzzleButton::Num7); }
	FORCEINLINE void OnPressNum8() { PerformButtonInteraction(EPasswordPuzzleButton::Num8); }
	FORCEINLINE void OnPressNum9() { PerformButtonInteraction(EPasswordPuzzleButton::Num9); }
	FORCEINLINE void OnPressDelete() { PerformButtonInteraction(EPasswordPuzzleButton::Delete); }
	FORCEINLINE void OnPressConfirm() { PerformButtonInteraction(EPasswordPuzzleButton::Confirm); }
	
public:
	FORCEINLINE UButton* GetButtonByIndex(const EPasswordPuzzleButton InButton) { return ButtonArray[InButton]; }
};
