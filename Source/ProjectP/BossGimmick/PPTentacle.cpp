// Fill out your copyright notice in the Description page of Project Settings.


#include "PPTentacle.h"

#include "PPWarningZoneCylinder.h"

// Sets default values
APPTentacle::APPTentacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//WarningZone = CreateDefaultSubobject<APPWarningZoneCylinder>(TEXT("WarningZone"));
}

// Called when the game starts or when spawned
void APPTentacle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APPTentacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPTentacle::ShowWarningSign()
{
	WarningZone = GetWorld()->SpawnActor<APPWarningZoneCylinder>(GetActorLocation(), FRotator::ZeroRotator);
	WarningZone->Show(1.0f);
}

void APPTentacle::HideWarningSignAndAttack()
{
	if (WarningZone)
	{
		WarningZone->Destroy();
	}
}
