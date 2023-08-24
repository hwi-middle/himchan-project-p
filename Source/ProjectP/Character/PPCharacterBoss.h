// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/BossGimmick/Leaf.h"
#include "ProjectP/Character/PPCharacterEnemy.h"
#include "ProjectP/Enumeration/PPBossPattern.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "Sound/SoundCue.h"
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
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }
	void SetIsAttacking(const bool Value);

	// TestOnly
	void TestPattern(EBossPattern Pattern);

protected:
	//virtual void SetupCharacterStatusData(UDataAsset* CharacterStatusData) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	EBossPattern GetRandomPattern() const;

private:
	void ClearAllTimerOnLevelChange();
	void GenerateTentaclesOnRandomLocation(uint32 InNum);
	void GenerateLeafTempestOnRandomLocation(uint32 InNum);
	void GenerateToxicFog();

private:
	// 보스 정보
	UPROPERTY(EditDefaultsOnly, Category = BossStatus)
	float Health;

	UPROPERTY()
	TObjectPtr<class UPPVRBossData> BossData;

	UPROPERTY()
	TObjectPtr<class UPPBossAnimInstance> AnimInstance;

	UPROPERTY()
	uint32 bIsAttacking : 1;

	UPROPERTY()
	float ElapsedAttackDelay;

	UPROPERTY()
	float AttackDelay;

	UPROPERTY()
	float AttackDelayMin;

	UPROPERTY()
	float AttackDelayMax;

	UPROPERTY()
	EBossPattern PreviousPattern;

	// 기믹
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	TMap<EBossPattern, uint32> BossPatternDamage;

	UPROPERTY()
	TObjectPtr<class UPPBossGimmickData> BossGimmickData;

	// 기믹 - 덩굴정원
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	uint32 VG_TentacleNum;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_MinDistance;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float VG_MaxDistance;
	
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	TObjectPtr<USoundCue> VG_OmenSound;

	// 기믹 - 리프 템페스트
	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	uint32 LT_LeafNum;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	TObjectPtr<USoundCue> LT_OmenSound;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	float LT_TraceDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	TArray<ALeaf*> LT_OnStage;

	UPROPERTY()
	FTimerHandle LT_OnStageSilentTimer;
	
	// 기믹 - 녹빛 안개
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UNiagaraComponent> GF_FX;

	UPROPERTY()
	FTimerHandle GreenFogTimerHandle;

	UPROPERTY()
	float GF_ElapsedTime;

	UPROPERTY(EditDefaultsOnly, Category = GreenFog)
	float GF_Damage;

	UPROPERTY(EditDefaultsOnly, Category = GreenFog)
	float GF_Duration;

	UPROPERTY(EditDefaultsOnly, Category = GreenFog)
	float GF_Radius;

	UPROPERTY(EditDefaultsOnly, Category = GreenFog)
	TObjectPtr<USoundCue> GF_OmenSound;

	UPROPERTY(EditDefaultsOnly, Category = GreenFog)
	TObjectPtr<USoundCue> GF_SpawnSound;

	UPROPERTY(EditDefaultsOnly, Category = GreenFog)
	uint32 bHasGFSpawned : 1;

	// 커맨더 사운드
private:
	UPROPERTY(EditDefaultsOnly, Category = Commander)
	TArray<USoundCue*> VG_CommanderSoundCueArray;
	
	UPROPERTY(EditDefaultsOnly, Category = Commander)
	TArray<USoundCue*> LT_CommanderSoundCueArray;
	
	UPROPERTY(EditDefaultsOnly, Category = Commander)
	TArray<USoundCue*> GF_CommanderSoundCueArray;
	
	UPROPERTY()
	uint32 bIs_VG_FirstUsed : 1;
	
	UPROPERTY()
	uint32 bIs_LT_FirstUsed : 1;

	UPROPERTY()
	uint32 bIs_GF_FirstUsed : 1;
};
