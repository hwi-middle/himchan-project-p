// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProjectP/Enumeration/PPVRGrabType.h"
#include "PPVRGrabComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(OnGrabEvent, class APPVRHand* hand)
DECLARE_MULTICAST_DELEGATE_OneParam(OnReleaseEvent, class APPVRHand* hand)

UENUM()
enum class EGrabObjectTypes : uint8
{
	Prop,
	Grenade,
	Gun
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTP_API UPPVRGrabComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPPVRGrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE void SetIsWeapon(const bool Value) { bIsWeapon = Value; }
	FORCEINLINE APPVRHand* GetGrabbingHand() const { return GrabbingHand; }
	FORCEINLINE bool GetIsWeapon() const { return bIsWeapon; }
	FORCEINLINE void SetGrabType(const EVRGrabType Value) { GrabType = Value; }
	FORCEINLINE void SetMainHandType(const EControllerHand Value) { MainHandType = Value; }
	FORCEINLINE void SetGrabObjectType(const EGrabObjectTypes ObjectType) { GrabObjectType = ObjectType; }
private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	uint32 bShouldSimulateOnDrop : 1;

	UPROPERTY()
	uint32 bHeld : 1;

	UPROPERTY()
	uint32 bIsWeapon : 1;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	EVRGrabType GrabType;

	UPROPERTY()
	TObjectPtr<class APPVRHand> GrabbingHand;

	UPROPERTY()
	EControllerHand MainHandType;

	UPROPERTY()
	EGrabObjectTypes GrabObjectType;
	
public:
	bool TryGrab(class APPVRHand* InHand);
	void TryRelease();
	void SetPrimitiveCompPhysics(bool bInSimulate);
	FORCEINLINE void SetShouldSimulateOnDrop(const bool bInSimulate) { bShouldSimulateOnDrop = bInSimulate; }

private:
	void TryAttachComponentToHand(APPVRHand* InHand);
	void TryAttachHandToComponent(APPVRHand* InHand);

public:
	OnGrabEvent OnGrab;
	OnReleaseEvent OnRelease;
};
