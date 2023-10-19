// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/LevelPuzzle/PPCircuitPuzzleWidget.h"

void UPPCircuitPuzzleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FirstCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassFirstCircuitWidget);
	SecondCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassSecondCircuitWidget);
	ThirdCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassThirdCircuitWidget);
}

void UPPCircuitPuzzleWidget::SetDefaultAngle(uint32 First, uint32 Second, uint32 Third)
{
	FirstCircuit->SetRenderTransformAngle(90 * First);
	SecondCircuit->SetRenderTransformAngle(90 * Second);
	ThirdCircuit->SetRenderTransformAngle(90 * Third);
}
