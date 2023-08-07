// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSettingBaseActor.h"

// Sets default values
APPSettingBaseActor::APPSettingBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APPSettingBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPSettingBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

