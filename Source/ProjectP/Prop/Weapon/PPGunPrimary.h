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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = DataAsset)
	TObjectPtr<class UPPWeaponData> PrimaryWeaponData;
};
