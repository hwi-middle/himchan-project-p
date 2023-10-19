// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/LevelEnterTriggerActor.h"

// Sets default values
ALevelEnterTriggerActor::ALevelEnterTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelEnterTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelEnterTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

