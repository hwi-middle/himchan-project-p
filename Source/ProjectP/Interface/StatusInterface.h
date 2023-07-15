// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectP/Character/PPCharacterStatusData.h"
#include "StatusInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * State interface for inheriting 'PPCharacterBase'
 */
class PROJECTP_API IStatusInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 기본 생성자 및 상태 변환
	virtual void SetupCharacterStatusData(const class UPPCharacterStatusData* CharacterStatusData) = 0;
	virtual void SetIdleState() = 0;
	virtual void SetDeadState() = 0;
	
	const virtual float GetCurrentHealth() = 0;
	virtual void RecoveryHealth(const float Health) = 0;
	
	const virtual uint8 GetCurrentState() = 0;
};
