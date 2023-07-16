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
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* ReloadSound;
	
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* FireSound;

	// 애님 몽타주와 시퀀스중 어떤 것을 사용할지는 나중에 결정
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 WeaponMagazineAmmo;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float WeaponShootRate;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float WeaponReloadDelay;
	
	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 WeaponBodyDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 WeaponBodyDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 WeaponHeadDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 WeaponHeadDamageMax;
};
