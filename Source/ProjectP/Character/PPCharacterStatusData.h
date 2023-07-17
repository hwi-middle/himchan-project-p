// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPCharacterStatusData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPCharacterStatusData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPPCharacterStatusData();

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 DefaultHealth;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 RecoveryHealthValueOnIdle;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float RunSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float ReturnToIdleStateTime;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float DestroyTime;
};
