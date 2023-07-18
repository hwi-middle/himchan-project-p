// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Enumeration/PPGunState.h"
#include "ProjectP/Prop/Weapon/PPWeaponData.h"
#include "GameFramework/Actor.h"
#include "PPGunBase.generated.h"

UCLASS()
class PROJECTP_API APPGunBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APPGunBase();

protected:
	virtual void SetupWeaponData(UPPWeaponData* WeaponData);
	
	void PressTrigger();
	void OnFire();
	void ReloadMagazine();
	void GrabOnHand();
	void RemoveOnHand();
	void ToggleLaserPoint();
	void ToggleFlashlight();

	FORCEINLINE void SetGunState(const EGunState EState) { CurrentState = EState; }
	FORCEINLINE EGunState GetGunState() const { return CurrentState; }
private:
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* BaseWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzlePosition;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* LaserPosition;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* FlashPosition;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* GripPosition;
	
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

	UPROPERTY(EditAnywhere, Category = WeaponStatus)
	EGunState CurrentState;
	
	uint32 bIsLaserPointEnable : 1;
	uint32 bIsFlashlightEnable : 1;
	uint32 bIsGrabbed : 1;
};
