// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/LevelPuzzle/PPCircuitPuzzleWidget.h"

void UPPCircuitPuzzleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FirstCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassFirstCircuitWidget);
	SecondCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassSecondCircuitWidget);
	ThirdCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassThirdCircuitWidget);

	for (uint32 i = 1; i <= CableNum; i++)
	{
		Cables.Emplace(CastChecked<UImage>(GetWidgetFromName(*FString::Printf(TEXT("Cable%d"), i))));
	}
}

void UPPCircuitPuzzleWidget::SetEnableTint()
{
	for	(auto Image : Cables)
	{
		Image->SetColorAndOpacity(FLinearColor::Yellow);
	}
}

void UPPCircuitPuzzleWidget::SetDefaultAngle(uint32 First, uint32 Second, uint32 Third)
{
	FirstCircuit->SetRenderTransformAngle(90 * First);
	SecondCircuit->SetRenderTransformAngle(90 * Second);
	ThirdCircuit->SetRenderTransformAngle(90 * Third);
}
