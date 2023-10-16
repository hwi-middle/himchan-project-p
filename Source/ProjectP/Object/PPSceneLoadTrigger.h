// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/Actor.h"
#include "PPSceneLoadTrigger.generated.h"

UCLASS()
class PROJECTP_API APPSceneLoadTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPSceneLoadTrigger();
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	void LoadLevelSequence();
	
private:
	void LoadLevelDelegate();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> TriggerBox;
	
private:
	UPROPERTY()
	TObjectPtr<APostProcessVolume> PostProcessVolume;

	UPROPERTY()
	FTimerHandle LoadLevelTimerHandle;

};
