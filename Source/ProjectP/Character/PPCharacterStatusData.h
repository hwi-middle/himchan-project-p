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

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	uint32 CharacterDefaultHealth;
	
	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	uint32 CharacterRecoveryHealthOnIdle;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float CharacterWalkSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float CharacterRunSpeed;
	
	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float ReturnToIdleStateTime;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float CharacterDestroyTime;
};
