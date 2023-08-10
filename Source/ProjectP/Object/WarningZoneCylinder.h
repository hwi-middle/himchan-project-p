// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarningZoneBase.h"
#include "WarningZoneBase.h"
#include "WarningZoneCylinder.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWarningZoneCylinder : public AWarningZoneBase
{
	GENERATED_BODY()
	
public:
	AWarningZoneCylinder();

protected:
	virtual void BeginPlay() override;

public:

};
