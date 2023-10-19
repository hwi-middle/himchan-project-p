// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPMusicTriggerActor.h"

// Sets default values
APPMusicTriggerActor::APPMusicTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APPMusicTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPMusicTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

