// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPMusicTriggerActor.h"

#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Game/PPGameInstance.h"

// Sets default values
APPMusicTriggerActor::APPMusicTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsFirstEnter = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
}

// Called when the game starts or when spawned
void APPMusicTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APPMusicTriggerActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(!bIsFirstEnter)
	{
		return;
	}
	APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(OtherActor);
	if(Player)
	{
		if(Player->GetAudioComponent()->IsPlaying())
		{
			Player->GetAudioComponent()->Stop();
		}
		Player->GetAudioComponent()->SetSound(BackGroundSoundCue);
		Player->GetAudioComponent()->Play();
		bIsFirstEnter = false;
	}
}

// Called every frame
void APPMusicTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

