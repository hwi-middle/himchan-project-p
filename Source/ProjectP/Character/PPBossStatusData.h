// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectP/Enumeration/PPBossPattern.h"
#include "PPBossStatusData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPBossStatusData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPPBossStatusData();

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 DefaultHealth;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	TMap<EBossPattern ,uint32> BossPattenDamages;
};
