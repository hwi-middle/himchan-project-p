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
	virtual void BeginPlay() override;
	
	FORCEINLINE virtual void SetCharacterState(const ECharacterState EState) override { CurrentState = EState; }
	FORCEINLINE const virtual ECharacterState GetCurrentState() override { return CurrentState; }
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }
	
private:
	void GenerateTentaclesOnRandomLocation(uint32 InNum);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float Health;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	ECharacterState CurrentState;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	TMap<EBossPattern, uint32> BossPatternDamage;
	
	UPROPERTY()
	TSet<class APPTentacle*> Tentacles;
};
