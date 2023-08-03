// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPEndingUIWidget.h"

#include "Components/CanvasPanelSlot.h"

void UPPEndingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetScreenImage(0);
	CreditPanel->SetRenderOpacity(0.0f);
	CreditPanelSlot = CastChecked<UCanvasPanelSlot>(CreditPanel->Slot);
}

bool UPPEndingUIWidget::SetScreenImage(const uint32 ArrayNum)
{
	const uint32 ArraySize = ScreenImageArray.Num();
	if(ArraySize <= ArrayNum)
	{
		return false;
	}
	else
	{
		ScreenImage->SetBrushFromTexture(ScreenImageArray[ArrayNum]);
		CurrentImageNum = ArrayNum;
	}
	return true;
}

float UPPEndingUIWidget::AddCreditPosition(const float AddPosY)
{
	CreditPanelSlot->SetPosition(FVector2d(CreditPanelSlot->GetPosition().X, CreditPanelSlot->GetPosition().Y + AddPosY));
	return CreditPanelSlot->GetPosition().Y;
}


