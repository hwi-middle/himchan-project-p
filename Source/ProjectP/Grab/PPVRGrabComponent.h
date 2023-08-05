// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProjectP/Enumeration/PPVRGrabType.h"
#include "PPVRGrabComponent.generated.h"

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

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	uint32 bShouldSimulateOnDrop : 1;

	UPROPERTY()
	uint32 bHeld : 1;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	EVRGrabType GrabType;

	UPROPERTY()
	TObjectPtr<class APPVRHand> GrabbingHand;
	
public:
	bool TryGrab(class APPVRHand* InHand);
	void TryRelease();
	void SetPrimitiveCompPhysics(bool bInSimulate);
	void SetShouldSimulateOnDrop();

private:
	void TryAttachComponentToHand(APPVRHand* InHand);
	void TryAttachHandToComponent(APPVRHand* InHand);
};
