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
	
	void PressTrigger();
	void OnFire();
	void ReloadMagazine();
	void GrabOnHand();
	void RemoveOnHand();
	void ToggleLaserPoint();
	void ToggleFlashlight();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* BaseWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzleLocation;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* LaserLocation;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* FlashLocation;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* GripLocation;
	
	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 MagazineAmmo;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	float FireRate;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	float ReloadDelay;
	
	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 BodyDamageMin;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 BodyDamageMax;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 HeadDamageMin;

	UPROPERTY(VisibleDefaultsOnly, Category = WeaponData)
	uint32 HeadDamageMax;
	
	uint32 bLaserPointIsEnable : 1;
	uint32 bFlashlightIsEnable : 1;
	uint32 bIsGrabbed : 1;
};
