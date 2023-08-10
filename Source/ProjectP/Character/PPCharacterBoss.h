// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Character/PPCharacterEnemy.h"
#include "ProjectP/Enumeration/PPBossPattern.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "PPCharacterBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APPCharacterBoss : public APPCharacterEnemy, public ICharacterStatusInterface
{
	GENERATED_BODY()
public:
	APPCharacterBoss();
	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	
protected:
	virtual void SetupCharacterStatusData(UDataAsset* CharacterStatusData) override;
	
	FORCEINLINE virtual void SetCharacterState(const ECharacterState EState) override { CurrentState = EState; }
	FORCEINLINE const virtual ECharacterState GetCurrentState() override { return CurrentState; }
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }
	
private:
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 Health;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	ECharacterState CurrentState;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	TMap<EBossPattern, uint32> BossPatternDamage;

	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	float GenerateWeakPointTime;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	uint32 RequiredWeakPointDestructionCount;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	float NeutralizeTime;
};
