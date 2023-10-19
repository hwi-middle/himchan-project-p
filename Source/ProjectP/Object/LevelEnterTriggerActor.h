// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/Actor.h"
#include "LevelEnterTriggerActor.generated.h"

UCLASS()
class PROJECTP_API ALevelEnterTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelEnterTriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void LevelStartDelegate();
private:
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY()
	TObjectPtr<APostProcessVolume> PostProcessVolume;

	UPROPERTY()
	float SavedExposureValue;
	
	UPROPERTY()
	float SavedVignetteValue;
};
