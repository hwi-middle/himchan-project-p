// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPlayerController.h"

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
