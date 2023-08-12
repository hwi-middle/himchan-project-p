// Fill out your copyright notice in the Description page of Project Settings.


#include "PPWarningZoneBase.h"

#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPWarningZoneBase::APPWarningZoneBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Opacity = 0.8f;
}

// Called when the game starts or when spawned
void APPWarningZoneBase::BeginPlay()
{
	Super::BeginPlay();
	Show(1.0f);
}

// Called every frame
void APPWarningZoneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APPWarningZoneBase::Show(float InDuration)
{
	Alpha = 0.f;
	FadeTimerRate = 0.01f;
	Duration = 1.0f;
	
	GetWorldTimerManager().SetTimer(FadeTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		Alpha += 1 / Duration * FadeTimerRate;
		Mesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), Alpha);
		if (Alpha >= Opacity)
		{
			Mesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), Opacity);
			GetWorldTimerManager().ClearTimer(FadeTimerHandle);
		}
	}), FadeTimerRate, true);
}

void APPWarningZoneBase::Hide(float InDuration)
{
	Alpha = 1.f;
	FadeTimerRate = 0.01f;

	GetWorldTimerManager().SetTimer(FadeTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		Alpha -= 1 / InDuration * FadeTimerRate;
		Mesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), Alpha);
		if (Alpha <= KINDA_SMALL_NUMBER)
		{
			Mesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), 0.f);
			GetWorldTimerManager().ClearTimer(FadeTimerHandle);
		}
	}), FadeTimerRate, true);
}
