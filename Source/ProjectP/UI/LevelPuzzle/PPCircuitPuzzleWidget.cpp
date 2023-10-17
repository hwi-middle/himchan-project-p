// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/LevelPuzzle/PPCircuitPuzzleWidget.h"

void UPPCircuitPuzzleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	FirstCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassFirstCircuitWidget);
	SecondCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassSecondCircuitWidget);
	ThirdCircuit->OnClicked.AddDynamic(this, &UPPCircuitPuzzleWidget::PassThirdCircuitWidget);
	
}
