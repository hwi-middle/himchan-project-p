// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Prop/Weapon/PPWeaponData.h"
#include "ProjectP/Prop/Weapon/PPWeaponBase.h"
#include "PPWeaponPrimary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APPWeaponPrimary : public APPWeaponBase
{
	GENERATED_BODY()
public:
	APPWeaponPrimary();
	
protected:
	virtual void SetupWeaponData(UPPWeaponData* WeaponData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = DataAsset)
	UPPWeaponData* PrimaryWeaponData;
};
