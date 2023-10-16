// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPSceneLoadTrigger.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"

// Sets default values
APPSceneLoadTrigger::APPSceneLoadTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
}

// Called every frame
void APPSceneLoadTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void APPSceneLoadTrigger::BeginPlay()
{
	Super::BeginPlay();
	PostProcessVolume = CastChecked<APostProcessVolume>(GetWorld()->PostProcessVolumes[0]);
}

void APPSceneLoadTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	// APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(OtherActor);
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if(Player)
	{
		LoadLevelSequence();
	}
}

void APPSceneLoadTrigger::LoadLevelSequence()
{
	DisableInput(GetWorld()->GetFirstPlayerController());
	GetWorldTimerManager().SetTimerForNextTick(this, &APPSceneLoadTrigger::LoadLevelDelegate);
}

void APPSceneLoadTrigger::LoadLevelDelegate()
{
	if (PostProcessVolume->Settings.AutoExposureBias <= -5.0f && PostProcessVolume->Settings.VignetteIntensity >= 2.5f)
	{
		GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
		UGameplayStatics::OpenLevel(GetWorld(), ENDING_LEVEL);
		return;
	}
	PostProcessVolume->Settings.AutoExposureBias -= 0.02f;
	PostProcessVolume->Settings.VignetteIntensity += 0.01f;
	GetWorldTimerManager().SetTimerForNextTick(this, &APPSceneLoadTrigger::LoadLevelDelegate);
}



