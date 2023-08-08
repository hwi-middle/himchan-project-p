// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Prop/Weapon/PPGunPrimary.h"
#include "ProjectP/Util/PPConstructorHelper.h"

APPGunPrimary::APPGunPrimary()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FPPConstructorHelper::FindObjectAndInitialize<UPPWeaponData>(TEXT("/Script/ProjectP.PPWeaponData'/Game/DataAssets/Weapon/PrimaryWeaponData.PrimaryWeaponData'"), [&](UPPWeaponData* Data)
	{
		SetupWeaponData(Data);
	}, EAssertionLevel::Check);
}

void APPGunPrimary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPGunPrimary::BeginPlay()
{
	Super::BeginPlay();
}
