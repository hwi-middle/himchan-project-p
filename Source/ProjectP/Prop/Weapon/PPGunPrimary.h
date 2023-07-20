// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Prop/Weapon/PPWeaponData.h"
#include "ProjectP/Prop/Weapon/PPGunBase.h"
#include "PPGunPrimary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APPGunPrimary : public APPGunBase
{
	GENERATED_BODY()
public:
	APPGunPrimary();
	
protected:
	virtual void SetupWeaponData(UPPWeaponData* WeaponData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = DataAsset)
	TObjectPtr<class UPPWeaponData> PrimaryWeaponData;
};
