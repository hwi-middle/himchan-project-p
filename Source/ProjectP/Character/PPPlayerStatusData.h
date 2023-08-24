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
};
