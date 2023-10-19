// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/LevelEnterTriggerActor.h"

#include "ProjectP/Game/PPGameInstance.h"

// Sets default values
ALevelEnterTriggerActor::ALevelEnterTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelEnterTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	PostProcessVolume = Cast<APostProcessVolume>(GetWorld()->PostProcessVolumes[0]);
	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	UPPSaveSettingOption* SettingOption = GameInstance->GetSaveSettingOption();
	SavedExposureValue = SettingOption->DisplayBrightnessValue;
	SavedVignetteValue = SettingOption->DisplayVignettingValue;
	PostProcessVolume->Settings.AutoExposureBias = -8.f;
	PostProcessVolume->Settings.VignetteIntensity = 4.f;
	LevelStartDelegate();
}

// Called every frame
void ALevelEnterTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelEnterTriggerActor::LevelStartDelegate()
{
	if (PostProcessVolume->Settings.AutoExposureBias >= SavedExposureValue && PostProcessVolume->Settings.VignetteIntensity <= SavedVignetteValue)
	{
		PostProcessVolume->Settings.AutoExposureBias = SavedExposureValue;
		PostProcessVolume->Settings.VignetteIntensity = SavedVignetteValue;
		return;
	}
	PostProcessVolume->Settings.AutoExposureBias += 0.02f;
	PostProcessVolume->Settings.VignetteIntensity -= 0.01f;
	GetWorldTimerManager().SetTimerForNextTick(this, &ALevelEnterTriggerActor::LevelStartDelegate);
}
