// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EGunState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Fire UMETA(DisplayName = "Fire"),
	Reload UMETA(DisplayName = "Reload")
};
