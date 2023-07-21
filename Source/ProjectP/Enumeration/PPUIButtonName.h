// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EUIButtonName : uint8
{
	Setting UMETA(DisplayName = "Setting"),
	Help UMETA(DisplayName = "Help"),
	ExitGame UMETA(DisplayName = "ExitGame"),
	Pause UMETA(DisplayName = "Pause")
};
