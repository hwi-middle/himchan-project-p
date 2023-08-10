// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Actor.h"
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
	TObjectPtr<class UMotionControllerComponent> MotionController;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetInteractionComponent> HandWidgetInteraction;
	
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UPPVRHandAnimInstance> HandAnimInstanceClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPPVRHandAnimInstance> AnimInstance;

public:
	void SetPoseAlphaGrasp(float Value);
	void SetPoseAlphaIndexCurl(const float Value);
	void SetPoseAlphaThumbUp(const float Value);
	void SetPoseAlphaPoint(const float Value);
	void WidgetInteractionToggle(const float Value);
	FORCEINLINE void WidgetInteractionDisable() { HandWidgetInteraction->InteractionDistance = 0.0f; };
	void InitHand();
};
