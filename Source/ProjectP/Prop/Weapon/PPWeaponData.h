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
	uint32 NormalShotDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 NormalShotDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 HeadShotDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 HeadShotDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 MaxOverheat;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 OverheatCoolDownPerSecond;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float UnavailableTime;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float OverheatAmountPerSingleShoot;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float ShootPerSecond;


	// UPROPERTY(EditDefaultsOnly, Category = Sound)
	// TObjectPtr<class USoundBase> ReloadSound;
	//
	// UPROPERTY(EditDefaultsOnly, Category = Sound)
	// TObjectPtr<class USoundBase> FireSound;
	//
	// UPROPERTY(EditDefaultsOnly, Category = Animation)
	// TObjectPtr<class UAnimMontage> FireAnimation;
};
