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
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData, DisplayName="Damage")
	float VG_Damage;
	
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData, DisplayName="TentacleNum")
	uint32 VG_TentacleNum;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData, DisplayName="MinDistance")
	float VG_MinDistance;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData, DisplayName="MaxDistance")
	float VG_MaxDistance;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData, DisplayName="WarningFadeInDuration")
	float VG_WarningFadeInDuration;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData, DisplayName="WarningFadeOutDuration")
	float VG_WarningFadeOutDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData, DisplayName="WarningDuration")
	float VG_WarningDuration;

	// 리프 템페스트
	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="Damage")
	float LT_Damage;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="LeafNum")
	uint32 LT_LeafNum;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="TraceStartDelay")
	float LT_TraceStartDelay;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="MinMoveSpeed")
	float LT_MinMoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="MaxMoveSpeed")
	float LT_MaxMoveSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="MinRotateSpeed")
	float LT_MinRotateSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="MaxRotateSpeed")
	float LT_MaxRotateSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="TraceDuration")
	float LT_TraceDuration;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="ExplodeDelay")
	float LT_BlinkDuration;
	
	UPROPERTY(EditDefaultsOnly, Category = LeafTempestData, DisplayName="BlinkSpeed")
	float LT_BlinkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = LeafTempest, DisplayName="FadeOutDuration")
	float LT_FadeOutDuration;
	
	// 녹빛 안개
	UPROPERTY(EditDefaultsOnly, Category = GreenFogData, DisplayName="Damage")
	float GF_Damage;
	
	UPROPERTY(EditDefaultsOnly, Category = GreenFogData, DisplayName="Duration")
	float GF_Duration;

	UPROPERTY(EditDefaultsOnly, Category = GreenFogData, DisplayName="Radius")
	float GF_Radius;
};
