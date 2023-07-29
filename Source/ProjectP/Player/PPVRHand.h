// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FORCEINLINE EControllerHand GetHandType() const { return HandType; }
	FORCEINLINE void SetHandType(const EControllerHand InHandType) { HandType = InHandType; }

private:
	UPROPERTY(VisibleAnywhere)
	EControllerHand HandType;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkeletalMeshComponent> HandMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UMotionControllerComponent> MotionController;
	
	void InitHand();
};
