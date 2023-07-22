// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectP/Character/PPPlayerStatusData.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
#include "CharacterStatusInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterStatusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * State interface for inheriting 'PPCharacterBase'
 */
class PROJECTP_API ICharacterStatusInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	// 기본 생성자 및 상태 변환
	virtual void SetupCharacterStatusData(const class UDataAsset* CharacterStatusData) = 0;
	
	virtual void SetCharacterState(const ECharacterState EState) = 0;
	const virtual ECharacterState GetCurrentState() = 0;

	virtual void IncreaseHealth(const float Value) = 0;
	virtual void DecreaseHealth(const float Value) = 0;
	const virtual float GetCurrentHealth() = 0;
};
