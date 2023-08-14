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
	void GenerateLeafTempestOnRandomLocation(uint32 InNum);
	
private:
	// 보스 정보
	UPROPERTY(EditDefaultsOnly, Category = BossStatus)
	float Health;

	// 기믹
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	TMap<EBossPattern, uint32> BossPatternDamage;
	
	UPROPERTY()
	TObjectPtr<class UPPBossGimmickData> BossGimmickData;
	
	// 기믹 - 덩굴정원
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_Damage;
	
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	uint32 VG_TentacleNum;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_MinDistance;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_MaxDistance;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_WarningFadeInDuration;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_WarningFadeOutDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_WarningDuration;
	
	// 기믹 - 리프 템페스트
	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	uint32 LT_LeafNum;
	
	// UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	// ECharacterState CurrentState;
};
