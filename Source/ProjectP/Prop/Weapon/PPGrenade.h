// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPGrenade.generated.h"

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

private:
	void Activate();
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY()
	TObjectPtr<class UPPVRGrabComponent> GrabComponent;

	UPROPERTY()
	uint32 bIsActivated : 1;

	UPROPERTY()	
	float ElapsedActivatedTime;

	UPROPERTY()	
	float ExplodeDelay;
};
