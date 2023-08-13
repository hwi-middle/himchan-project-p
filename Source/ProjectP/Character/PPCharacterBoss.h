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
	
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }
	
private:
	void GenerateTentaclesOnRandomLocation(uint32 InNum);
	
private:
	// 보스 정보
	UPROPERTY(EditDefaultsOnly, Category = BossStatus)
	float Health;

	// 기믹 - 덩굴정원
	UPROPERTY()
	TObjectPtr<class UPPBossGimmickData> BossPatternData;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VineGardenDamage;
	
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	uint32 TentacleNum;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float MinDistance;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float MaxDistance;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float WarningFadeInDuration;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float WarningFadeOutDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float WarningDuration;
	

	
	// UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	// ECharacterState CurrentState;

	// UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	// TMap<EBossPattern, uint32> BossPatternDamage;
	
	UPROPERTY()
	TSet<class APPTentacle*> Tentacles;
};
