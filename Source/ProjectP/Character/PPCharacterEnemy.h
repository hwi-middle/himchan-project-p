// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Character/PPCharacterBase.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "PPCharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APPCharacterEnemy : public APPCharacterBase, public ICharacterStatusInterface
{
	GENERATED_BODY()
	
public:
	APPCharacterEnemy();
	
	// 인터페이스 구현
	virtual void IncreaseHealth(const float Value) override { }
	virtual void DecreaseHealth(const float Value) override { }
	FORCEINLINE const virtual float GetCurrentHealth() override { return 0; }
};
