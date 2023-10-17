// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPasswordPuzzleWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPPPasswordPuzzleWidget::NativeConstruct()
{
	MaxDigit = 4;
	CurrentDigit = 0;

	for (uint32 i = 1; i <= MaxDigit; i++)
	{
		PasswordDigitArray.Emplace(CastChecked<UTextBlock>(GetWidgetFromName(*FString::Printf(TEXT("PWDigit_%d"), i))));
	}
	
	for (int i = EPasswordPuzzleButton::Num0; i <= EPasswordPuzzleButton::Num9; i++)
	{
		ButtonArray.Emplace(CastChecked<UButton>(GetWidgetFromName(*FString::Printf(TEXT("PWBtn_%d"), i))));
	}
	ButtonArray.Emplace(CastChecked<UButton>(GetWidgetFromName(TEXT("PWBtn_Delete"))));
	ButtonArray.Emplace(CastChecked<UButton>(GetWidgetFromName(TEXT("PWBtn_Confirm"))));

	for (uint32 i = 0; i < MaxDigit; i++)
	{
		PasswordDigitArray[i]->SetText(FText::FromString(TEXT("")));
	}
	
	ButtonArray[EPasswordPuzzleButton::Num0]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum0);
	ButtonArray[EPasswordPuzzleButton::Num1]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum1);
	ButtonArray[EPasswordPuzzleButton::Num2]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum2);
	ButtonArray[EPasswordPuzzleButton::Num3]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum3);
	ButtonArray[EPasswordPuzzleButton::Num4]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum4);
	ButtonArray[EPasswordPuzzleButton::Num5]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum5);
	ButtonArray[EPasswordPuzzleButton::Num6]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum6);
	ButtonArray[EPasswordPuzzleButton::Num7]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum7);
	ButtonArray[EPasswordPuzzleButton::Num8]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum8);
	ButtonArray[EPasswordPuzzleButton::Num9]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressNum9);
	ButtonArray[EPasswordPuzzleButton::Delete]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressDelete);
	ButtonArray[EPasswordPuzzleButton::Confirm]->OnClicked.AddDynamic(this, &UPPPasswordPuzzleWidget::OnPressConfirm);
	UE_LOG(LogTemp, Log, TEXT("NativeConstruct"));

}

void UPPPasswordPuzzleWidget::PerformButtonInteraction(const EPasswordPuzzleButton InButton)
{
	UE_LOG(LogTemp, Log, TEXT("PerformButtonInteraction"));
	switch (InButton)
	{
	case Num0:
	case Num1:
	case Num2:
	case Num3:
	case Num4:
	case Num5:
	case Num6:
	case Num7:
	case Num8:
	case Num9:
		AppendPasswordDigit(InButton);
		break;
	case Delete:
		DeletePasswordDigit();
		break;
	case Confirm:
		// TODO
		break;
	default:
		checkNoEntry();
	}
}

void UPPPasswordPuzzleWidget::AppendPasswordDigit(uint32 InDigit)
{
	UE_LOG(LogTemp, Log, TEXT("LOG"));
	if (CurrentDigit >= MaxDigit)
	{
		return;
	}

	PasswordDigitArray[CurrentDigit++]->SetText(FText::FromString(FString::Printf(TEXT("%d"), InDigit)));
}

void UPPPasswordPuzzleWidget::DeletePasswordDigit()
{
	PasswordDigitArray[CurrentDigit--]->SetText(FText::FromString(TEXT("")));
}
