// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPEventReceiver.h"

APPEventReceiver::APPEventReceiver()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts
void APPEventReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

void APPEventReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APPEventReceiver::AddEventStack()
{
	CurrentEventStack++;
	if(CurrentEventStack >= ActivationEventStack)
	{
		EventReceivingDelegate.Broadcast();
	}
}
