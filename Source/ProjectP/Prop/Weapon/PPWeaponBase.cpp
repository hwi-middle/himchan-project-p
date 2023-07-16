// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Prop/Weapon/PPWeaponBase.h"

// Sets default values
APPWeaponBase::APPWeaponBase()
{
	BaseWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(BaseWeaponMesh);

	LaserLocation = CreateDefaultSubobject<USceneComponent>(TEXT("LaserLocation"));
	LaserLocation->SetupAttachment(BaseWeaponMesh);
	
	TorchLocation = CreateDefaultSubobject<USceneComponent>(TEXT("TorchLocation"));
	TorchLocation->SetupAttachment(BaseWeaponMesh);
	
	GripLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GripLocation"));
	GripLocation->SetupAttachment(BaseWeaponMesh);
	
}

void APPWeaponBase::SetupWeaponData(UPPWeaponData* WeaponData)
{
	BaseWeaponMagazineAmmo = WeaponData->WeaponMagazineAmmo;
	BaseWeaponReloadDelay = WeaponData->WeaponReloadDelay;
	BaseWeaponShootRate = WeaponData->WeaponShootRate;
	BaseWeaponBodyDamageMin = WeaponData->WeaponBodyDamageMin;
	BaseWeaponBodyDamageMax = WeaponData->WeaponBodyDamageMax;
	BaseWeaponHeadDamageMin = WeaponData->WeaponHeadDamageMin;
	BaseWeaponHeadDamageMax = WeaponData->WeaponHeadDamageMax;
}

void APPWeaponBase::WeaponTriggered()
{
	/*
	 * Called to Player InputAction
	 * Check Ammo remain
	 * Call OnFire every BaseWeaponShootRate seconds
	 * Change weapon's state to Fire?
	 */
}

void APPWeaponBase::OnFire()
{
	/*
	 * Called to WeaponTriggered Function
	 * Use Trace and HitResult
	 */
}

void APPWeaponBase::ReloadMagazine()
{
	/*
	 * Play weapon's Reload Animation
	 * Disable fire when BaseWeaponReloadDelay seconds
	 */
}

void APPWeaponBase::GrabbedOnHand()
{
	/*
	 * Enable weapon input mapping context
	 * GripLocation hold to player controller's hand position
	 */
	bIsGrabbed = true;
}

void APPWeaponBase::DroppedOnHand()
{
	/*
	* Disable weapon input mapping context
	*/
	bIsGrabbed = false;
}

void APPWeaponBase::ToggleLaserPoint()
{
	if(!bEnableLaserPoint)
	{
		/*
		 * Do something
		 */
		bEnableLaserPoint = true;
	}
	else
	{
		/*
		 * Do something
		 */
		bEnableLaserPoint = false;
	}
}

void APPWeaponBase::ToggleTorchlight()
{
	if(!bEnableTorchlight)
	{
		/*
		 * Do something
		 */
		bEnableTorchlight = true;
	}
	else
	{
		/*
		 * Do something
		 */
		bEnableTorchlight = false;
	}
}

