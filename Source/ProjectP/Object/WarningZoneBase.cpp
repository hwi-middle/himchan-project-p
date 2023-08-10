// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningZoneBase.h"

#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
AWarningZoneBase::AWarningZoneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWarningZoneBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarningZoneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

