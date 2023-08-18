// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Enumeration/PPGunState.h"
#include "ProjectP/Prop/Weapon/PPWeaponData.h"
#include "Components/SpotLightComponent.h"
#include "ProjectP/Constant/PPSkeletalMeshSocketName.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "Engine/SkeletalMeshSocket.h"
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
	void StopFire();
	void ToggleFlash();
	
	// Test Only
	float ElapsedUnavailableTime;
	FORCEINLINE float GetCurrentOverheatGauge() const { return CurrentOverheat; }
	FORCEINLINE float GetUnavailableTimeRemains() const { return bIsUnavailable ? (UnavailableTime - ElapsedUnavailableTime) : 0; }
	FORCEINLINE FString GetAimingActorName() const { return AimingActor != nullptr ? AimingActor->GetActorNameOrLabel() : FString::Printf(TEXT("None")); }
	//
	
protected:
	void SetupWeaponData(UPPWeaponData* WeaponData);
	void PressTrigger();
	void GrabOnHand(class APPVRHand* InHand);
	void ReleaseOnHand(class APPVRHand* InHand);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<class UStaticMeshComponent> CrossHairPlane;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<class UNiagaraComponent> MuzzleNiagaraEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<USpotLightComponent> Flashlight;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TObjectPtr<class UPPVRGrabComponent> GrabComponent;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float NormalShotDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float NormalShotDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float HeadShotDamageMin;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float HeadShotDamageMax;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float CurrentOverheat;
	
	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float OverheatAmountPerSingleShoot;
	
	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float MaxOverheat;
	
	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float UnavailableTime;
	
	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float ShootPerSecond;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float ShootDelayPerShoot;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponData")
	float CooldownDelay;
	
	UPROPERTY()
	float OverheatCoolDownPerSecond;

	UPROPERTY()
	float ElapsedTimeAfterLastShoot;

	// UPROPERTY()
	// uint32 bIsOverheated : 1;

	UPROPERTY()
	uint32 bIsOnShooting : 1;
	
	UPROPERTY()
	uint32 bIsUnavailable : 1;

	UPROPERTY()
	uint32 bHeld : 1;

private:
	UPROPERTY(EditDefaultsOnly, Category = "CrossHair")
	TObjectPtr<class UStaticMesh> DefaultCrossHair;
	
	UPROPERTY(EditDefaultsOnly, Category = "CrossHair")
	TObjectPtr<class UStaticMesh> OverheatedCrossHair;
	
private:
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

	UPROPERTY()
	FColor LineColor;
	
	uint32 bIsFlashlightEnable : 1;

	UPROPERTY()
	FTimerHandle BlockShootTimerHandle;
	
	UPROPERTY()
	FTimerHandle OverheatCoolDownTimerHandle;

private:
	void SetupInputMappingContextByHandType(const EControllerHand InHandType);
	
};
