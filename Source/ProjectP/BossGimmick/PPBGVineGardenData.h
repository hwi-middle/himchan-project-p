// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPBGVineGardenData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPBGVineGardenData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	float Damage;
	
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
};
