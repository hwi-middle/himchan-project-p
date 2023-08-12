// Fill out your copyright notice in the Description page of Project Settings.


#include "PPTentacle.h"

#include "PPWarningZoneCylinder.h"

// Sets default values
APPTentacle::APPTentacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
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

void APPTentacle::ShowWarningSign(float InFadeInDuration, float InDelay, float InFadeOutDuration)
{
	WarningZone = GetWorld()->SpawnActor<APPWarningZoneCylinder>(GetActorLocation(), FRotator::ZeroRotator);
	WarningZone->Show(InFadeInDuration);
	GetWorldTimerManager().SetTimer(WarningTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		HideWarningSignAndAttack(InFadeOutDuration);
		GetWorldTimerManager().ClearTimer(WarningTimerHandle);
	}), InDelay, false);
}

void APPTentacle::HideWarningSignAndAttack(float InFadeOutDuration)
{
	if (WarningZone)
	{
		WarningZone->HideAndDestroy(InFadeOutDuration);
	}
}
