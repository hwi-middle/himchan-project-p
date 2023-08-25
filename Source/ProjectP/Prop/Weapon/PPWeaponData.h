// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPWeaponData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPPWeaponData();

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<class USkeletalMesh> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float ShootDistance;
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float NormalShotDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float NormalShotDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float HeadShotDamageScaleFactor;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float MaxOverheat;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float OverheatCoolDownPerSecond;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float UnavailableTime;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float OverheatAmountPerSingleShoot;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float ShootPerSecond;
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float CooldownDelay;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float FlashIntensity;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float FlashRadius;
};
