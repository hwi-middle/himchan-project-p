// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPDestructTrigger.h"

// Sets default values for this component's properties
UPPDestructTrigger::UPPDestructTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentTriggerStack = 0;
}

void UPPDestructTrigger::BeginPlay()
{
	Super::BeginPlay();

}

void UPPDestructTrigger::AddTriggerStack()
{
	CurrentTriggerStack++;
	if(CurrentTriggerStack == MaximumTriggerStack)
	{
		// Blueprint Event;
		DestructTriggerDelegate.Broadcast();
	}
}

