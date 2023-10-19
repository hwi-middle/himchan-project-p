// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPSceneLoadTriggerActor.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"

// Sets default values
APPSceneLoadTriggerActor::APPSceneLoadTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TargetExposureBias = 5.0f;
	TargetVignetteIntensity = 2.5f;
	AddExposureBias = 0.02f;
	AddVignetteIntensity = 0.01f;
}

// Called every frame
void APPSceneLoadTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void APPSceneLoadTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	PostProcessVolume = CastChecked<APostProcessVolume>(GetWorld()->PostProcessVolumes[0]);
}

void APPSceneLoadTriggerActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(OtherActor);
	if(Player)
	{
		DisableInput(GetWorld()->GetFirstPlayerController());
		LoadLevelSequence();
	}
}

void APPSceneLoadTriggerActor::LoadLevelSequence()
{
	DisableInput(GetWorld()->GetFirstPlayerController());
	GetWorldTimerManager().SetTimerForNextTick(this, &APPSceneLoadTriggerActor::LoadLevelDelegate);
}

void APPSceneLoadTriggerActor::LoadLevelDelegate()
{
	if (PostProcessVolume->Settings.AutoExposureBias <= TargetExposureBias && PostProcessVolume->Settings.VignetteIntensity >= TargetVignetteIntensity)
	{
		GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
		UGameplayStatics::OpenLevel(GetWorld(), ENDING_LEVEL);
		return;
	}
	PostProcessVolume->Settings.AutoExposureBias -= AddExposureBias;
	PostProcessVolume->Settings.VignetteIntensity += AddVignetteIntensity;
	GetWorldTimerManager().SetTimerForNextTick(this, &APPSceneLoadTriggerActor::LoadLevelDelegate);
}



