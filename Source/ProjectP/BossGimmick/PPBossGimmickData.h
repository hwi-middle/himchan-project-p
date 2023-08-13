// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPBossGimmickData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPBossGimmickData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	// 덩굴 정원
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

	// 리프 템페스트
	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	float LeafTempestDamage;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	uint32 LeafNum;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	float TraceStartDelay;
	
	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	float TraceDuration;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempest)
	float ExplodeDelay;
	
	// 녹빛 안개
};
