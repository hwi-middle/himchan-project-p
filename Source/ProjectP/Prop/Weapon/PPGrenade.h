// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Player/PPVRHand.h"
#include "PPGrenade.generated.h"

class UGrenadeData;

UENUM()
enum EGrenadeExplodeType : uint8
{
	OnImpact,
	OnImpactWithDelay,
	OnReleaseWithDelay
};

UCLASS()
class PROJECTP_API APPGrenade : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APPGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnGrab(APPVRHand* InHand);
	void OnRelease(APPVRHand* InHand);
	FORCEINLINE UPPVRGrabComponent* GetGrabComponent() const { return GrabComponent; }

private:
	void WaitForDelayAndExplode();
	void Explode();

private:
	UPROPERTY()
	TObjectPtr<UGrenadeData> GrenadeData;

	UPROPERTY()
	TEnumAsByte<EGrenadeExplodeType> ExplodeType;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY()
	TObjectPtr<class UPPVRGrabComponent> GrabComponent;

	UPROPERTY()
	uint32 bIsActivated : 1;

	UPROPERTY()
	uint32 bIsWaitingForDelay : 1;

	UPROPERTY()
	float ElapsedActivatedTime;

	UPROPERTY()
	float ExplodeDelay;

	UPROPERTY()
	float ActivateRadius;

	UPROPERTY()
	float ExplodeRadius;

	UPROPERTY()
	float ExplodeDamage;

	FCollisionQueryParams CollisionParamsOnTick;
};
