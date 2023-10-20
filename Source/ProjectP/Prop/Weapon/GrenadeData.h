// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GrenadeData.generated.h"

enum EGrenadeExplodeType : uint8;
/**
 * 
 */
UCLASS()
class PROJECTP_API UGrenadeData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, DisplayName="폭발 지연시간")
	float ExplodeDelay;

	UPROPERTY(EditAnywhere, DisplayName="폭발 타입")
	TEnumAsByte<EGrenadeExplodeType> ExplodeType;

	UPROPERTY(EditAnywhere, DisplayName="폭발 인지 반경(m)")
	float ActivateRadius;

	UPROPERTY(EditAnywhere, DisplayName="폭발 피해 반경(m)")
	float ExplodeRadius;
	
	UPROPERTY(EditAnywhere, DisplayName="폭발 피해량")
	float ExplodeDamage;
};
