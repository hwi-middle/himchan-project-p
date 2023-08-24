// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Grab/PPVRGrabComponent.h"
#include "MotionControllerComponent.h"
#include "Components/WidgetComponent.h"
#include "PPVRHand.generated.h"

/*
응애
 */
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

private:
	UPROPERTY(VisibleAnywhere)
	EControllerHand HandType;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> HandMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMotionControllerComponent> MotionController;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetInteractionComponent> HandWidgetInteraction;
	
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UPPVRHandAnimInstance> HandAnimInstanceClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPPVRHandAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere)
	float GripRadius;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPPVRGrabComponent> HeldComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> DebugWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> VitalWidgetComponent;
	
	UPROPERTY(VisibleAnywhere)
	FTransform InitHandMeshRelativeTransform;

	UPROPERTY()
	float OnGrabWeaponIndexCurlMinimumValue;

	UPROPERTY()
	uint32 bIsMainHand : 1;
	
public:
	UPPVRGrabComponent* FindGrabComponentNearby();
	void HandleGrab();
	void HandleRelease();
	void SetPoseAlphaGrasp(float Value);
	void SetPoseAlphaIndexCurl(const float Value);
	void SetPoseAlphaThumbUp(const float Value);
	void SetPoseAlphaPoint(const float Value);
	void WidgetInteractionToggle(const float Value);
	void InitHand();
	void ResetHandMesh();

public:
	FORCEINLINE class UMotionControllerComponent* GetMotionController() const { return MotionController; }
	FORCEINLINE class USkeletalMeshComponent* GetHandMesh() const { return HandMesh; }
	FORCEINLINE void SetHandType(const EControllerHand InHandType) { HandType = InHandType; }
	FORCEINLINE EControllerHand GetHandType() const { return HandType; }
	FORCEINLINE class UPPVRGrabComponent* GetHeldComponent() const { return HeldComponent; }
	FORCEINLINE void SetMainHand(const bool Value) { bIsMainHand = Value; }
	void DisableWidgetComponent() const;
	void SetupWidgetComponent(const float Value);
	void SetupVitalWidget();
	FORCEINLINE void SetVitalWidgetVisible(const bool Value) const { VitalWidgetComponent->SetVisibility(Value); }
	void SetupDebugWidget();
};
