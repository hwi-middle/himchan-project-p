// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EWidgetType : uint8
{
	Lobby UMETA(DisplayName = "Lobby"),
	Setting UMETA(DisplayName = "Setting"),
	Tutorial UMETA(DisplayName = "Tutorial"),
	ExitCheck UMETA(DisplayName = "ExitCheck"),
	Pause UMETA(DisplayName = "Pause")
};
