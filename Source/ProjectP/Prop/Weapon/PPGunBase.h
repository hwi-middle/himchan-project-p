// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Enumeration/PPGunState.h"
#include "ProjectP/Prop/Weapon/PPWeaponData.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "PPGunBase.generated.h"

UCLASS()
class PROJECTP_API APPGunBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APPGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnFire();

protected:
	void SetupWeaponData(UPPWeaponData* WeaponData);

	void PressTrigger();
	void GrabOnHand(class APPVRHand* InHand);
	void ReleaseOnHand(class APPVRHand* InHand);
	void ToggleLaserPoint();
	void ToggleFlashlight();

private:
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<class USceneComponent> MuzzlePosition;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<class USceneComponent> LaserPosition;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<class USceneComponent> FlashPosition;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<class USceneComponent> GripPosition;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TObjectPtr<class USceneComponent> GrabComponent;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 NormalShotDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 NormalShotDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 HeadShotDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 HeadShotDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	uint32 MaxOverheat;

	UPROPERTY(EditDefaultsOnly, Category = WeaponData)
	float UnavailableTime;

	UPROPERTY()
	TObjectPtr<class UInputAction> LeftShootAction;
	
	UPROPERTY()
	TObjectPtr<class UInputAction> RightShootAction;

	UPROPERTY()
	TObjectPtr<class UEnhancedInputLocalPlayerSubsystem> PlayerSubSystem;

	UPROPERTY()
	TObjectPtr<class UInputMappingContext> LeftHandInputMappingContext;

	UPROPERTY()
	TObjectPtr<class UInputMappingContext> RightHandInputMappingContext;

	UPROPERTY()
	TObjectPtr<class AActor> AimingActor;

	uint32 bIsLaserPointEnable : 1;
	uint32 bIsFlashlightEnable : 1;

private:
	void SetupInputMappingContextByHandType(const EControllerHand InHandType);
};
