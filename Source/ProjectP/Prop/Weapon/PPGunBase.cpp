// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Prop/Weapon/PPGunBase.h"

// Sets default values
APPGunBase::APPGunBase()
{
	BaseWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(BaseWeaponMesh);

	LaserLocation = CreateDefaultSubobject<USceneComponent>(TEXT("LaserLocation"));
	LaserLocation->SetupAttachment(BaseWeaponMesh);
	
	FlashLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FlashLocation"));
	FlashLocation->SetupAttachment(BaseWeaponMesh);
	
	GripLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GripLocation"));
	GripLocation->SetupAttachment(BaseWeaponMesh);
}

void APPGunBase::SetupWeaponData(UPPWeaponData* WeaponData)
{
	MagazineAmmo = WeaponData->MagazineAmmo;
	ReloadDelay = WeaponData->ReloadDelay;
	FireRate = WeaponData->FireRate;
	BodyDamageMin = WeaponData->BodyDamageMin;
	BodyDamageMax = WeaponData->BodyDamageMax;
	HeadDamageMin = WeaponData->HeadDamageMin;
	HeadDamageMax = WeaponData->HeadDamageMax;
}

void APPGunBase::PressTrigger()
{
	/*
	 * Called to Player InputAction
	 * Check Ammo remain
	 * If Ammo is left, Call OnFire every BaseWeaponShootRate seconds
	 * Change weapon's state to Fire
	 */
}

void APPGunBase::OnFire()
{
	/*
	 * Called to WeaponTriggered Function
	 * Use Trace and HitResult
	 */
}

void APPGunBase::ReloadMagazine()
{
	/*
	 * Play weapon's Reload Animation
	 * Disable fire when BaseWeaponReloadDelay seconds
	 */
}

void APPGunBase::GrabOnHand()
{
	/*
	 * Enable weapon input mapping context
	 * GripLocation hold to player controller's hand position
	 */
	bIsGrabbed = true;
}

void APPGunBase::RemoveOnHand()
{
	/*
	* Disable weapon input mapping context
	*/
	bIsGrabbed = false;
}

void APPGunBase::ToggleLaserPoint()
{
	if(!bLaserPointIsEnable)
	{
		/*
		 * Do something
		 */
		bLaserPointIsEnable = true;
	}
	else
	{
		/*
		 * Do something
		 */
		bLaserPointIsEnable = false;
	}
}

void APPGunBase::ToggleFlashlight()
{
	if(!bFlashlightIsEnable)
	{
		/*
		 * Do something
		 */
		bFlashlightIsEnable = true;
	}
	else
	{
		/*
		 * Do something
		 */
		bFlashlightIsEnable = false;
	}
}

