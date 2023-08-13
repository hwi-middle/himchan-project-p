// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPWarningZoneBase.h"
#include "PPWarningZoneBase.h"
#include "PPWarningZoneCylinder.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APPWarningZoneCylinder : public APPWarningZoneBase
{
	GENERATED_BODY()
	
public:
	APPWarningZoneCylinder();

protected:
	virtual void BeginPlay() override;

public:

};
