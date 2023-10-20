// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Player/PPVRHand.h"
#include "Sound/SoundCue.h"
#include "PPStorageableProp.generated.h"

UCLASS()
class PROJECTP_API APPStorageableProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPStorageableProp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnGrab(APPVRHand* InHand);
	void OnRelease(APPVRHand* InHand);
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY()
	TObjectPtr<class UPPVRGrabComponent> GrabComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> CommanderSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> GrabSound;
	
	UPROPERTY()
	uint32 bIsGrabbed: 1;
};



