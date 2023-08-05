// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Grab/PPVRGrabComponent.h"
#include "MotionControllerComponent.h"
#include "PPVRHand.generated.h"

UCLASS()
class PROJECTP_API APPVRHand : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APPVRHand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void SetHandType(const EControllerHand InHandType) { HandType = InHandType; }

private:
	UPROPERTY(VisibleAnywhere)
	EControllerHand HandType;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> HandMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMotionControllerComponent> MotionController;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UPPVRHandAnimInstance> HandAnimInstanceClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPPVRHandAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere)
	float GripRadius;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPPVRGrabComponent> HeldComponent;

	UPROPERTY(VisibleAnywhere)
	FTransform InitHandMeshRelativeTransform;

public:
	UPPVRGrabComponent* FindGrabComponentNearby();
	void HandleGrab();
	void HandleRelease();
	void SetPoseAlphaGrasp(float Value);
	void SetPoseAlphaIndexCurl(const float Value);
	void SetPoseAlphaThumbUp(const float Value);
	void SetPoseAlphaPoint(const float Value);
	void InitHand();
	void ResetHandMesh();

public:
	FORCEINLINE class UMotionControllerComponent* GetMotionController() const { return MotionController;}
	FORCEINLINE class USkeletalMeshComponent* GetHandMesh() const { return HandMesh;}
};
