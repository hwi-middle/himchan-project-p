// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum ECharacterState :uint8
{
	Sleep UMETA(DisplayName = "Sleep"),
	Idle UMETA(DisplayName = "Idle"),
	Awake UMETA(DisplayName = "Awake"),
	Tracking UMETA(DisplayName = "Tracking"),
	Attack UMETA(DisplayName = "Attack"),
	Hit UMETA(DisplayName = "Hit"),
	Dead UMETA(DisplayName = "Dead")
};
