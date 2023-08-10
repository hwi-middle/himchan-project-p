// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPVRBossData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPVRBossData : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = BossData)
	uint32 MaxHP;
	
	UPROPERTY(EditDefaultsOnly, Category = BossData)
	uint32 DamageMul;

	UPROPERTY(EditDefaultsOnly, Category = BossData)
	float ParalysisTime;

	UPROPERTY(EditDefaultsOnly, Category = BossData)
	float RespawnTimer;
};
