// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Prop/Weapon/PPWeaponData.h"
#include "GameFramework/Actor.h"
#include "PPWeaponBase.generated.h"

UENUM()
enum EWeaponState : uint8
{
	Idle,
	Fire,
	Reload
};

UCLASS()
class PROJECTP_API APPWeaponBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APPWeaponBase();

protected:
	virtual void SetupWeaponData(UPPWeaponData* WeaponData);

	void WeaponTriggered();
	void OnFire();
	void ReloadMagazine();
	void GrabbedOnHand();
	void DroppedOnHand();
	void ToggleLaserPoint();
	void ToggleTorchlight();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* BaseWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzleLocation;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* LaserLocation;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* TorchLocation;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* GripLocation;
	
	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 BaseWeaponMagazineAmmo;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	float BaseWeaponShootRate;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	float BaseWeaponReloadDelay;
	
	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 BaseWeaponBodyDamageMin;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 BaseWeaponBodyDamageMax;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 BaseWeaponHeadDamageMin;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 BaseWeaponHeadDamageMax;
	
	uint32 bEnableLaserPoint : 1;
	uint32 bEnableTorchlight : 1;
	uint32 bIsGrabbed : 1;
};
