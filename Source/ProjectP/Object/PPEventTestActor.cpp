// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPEventTestActor.h"

// Sets default values
APPEventTestActor::APPEventTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventCallerComponent = CreateDefaultSubobject<UPPEventCaller>(TEXT("EventCaller"));
}

// Called when the game starts or when spawned
void APPEventTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPEventTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

