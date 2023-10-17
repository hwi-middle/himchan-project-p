// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPPlayerStatusData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPPlayerStatusData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPPPlayerStatusData();

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float MaximumHealth;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float WarningHealth;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float RecoveryHealthAmountPerSecond;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float ReturnToIdleStateTime;

	UPROPERTY(EditDefaultsOnly, Category = Misc)
	float DamageFXFadeInDuration;

	UPROPERTY(EditDefaultsOnly, Category = Misc)
	float DamageFXFadeOutDuration;

	UPROPERTY(EditAnywhere, Category = Misc, DisplayName = "페이드 아웃 목표 노출 값(-)")
	float TargetExposureBias;
	
	UPROPERTY(EditAnywhere, Category = Misc, DisplayName = "페이드 아웃 목표 비네트 값(+)")
	float TargetVignetteIntensity;

	UPROPERTY(EditAnywhere, Category = Misc, DisplayName = "페이드 아웃 프레임당 노출 감소 값")
	float AddExposureBias;

	UPROPERTY(EditAnywhere, Category = Misc, DisplayName = "페이드 아웃 프레임당 비네트 증가 값")
	float AddVignetteIntensity;
};
