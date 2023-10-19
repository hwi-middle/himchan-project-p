// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "PPMusicTriggerActor.generated.h"

UCLASS()
class PROJECTP_API APPMusicTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPMusicTriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> BackGroundSoundCue;

	uint32 bIsFirstEnter : 1;
};
