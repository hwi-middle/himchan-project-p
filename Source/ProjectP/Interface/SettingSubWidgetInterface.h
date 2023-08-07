// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Util/PPSaveSettingOption.h"
#include "UObject/Interface.h"
#include "SettingSubWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USettingSubWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTP_API ISettingSubWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void SaveSettingData(UPPSaveSettingOption* SettingOption) = 0;
	virtual void LoadSettingData(UPPSaveSettingOption* SettingOption) = 0;
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
