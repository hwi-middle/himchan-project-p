// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Object/PPBossTriggerActor.h"

#include "GameFramework/Character.h"
#include "ProjectP/Player/PPVRPawn.h"

// Sets default values
APPBossTriggerActor::APPBossTriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	TriggerBox->SetBoxExtent(FVector(50,50,50));
	bIsLevelChanger = false;
}

// Called when the game starts or when spawned
void APPBossTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APPBossTriggerActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	TObjectPtr<APPVRPawn> Player = Cast<APPVRPawn>(OtherActor);
	TObjectPtr<ACharacter> TestPlayer = Cast<ACharacter>(OtherActor);
	if(Player || TestPlayer)
	{
		BossEnableDelegate.Broadcast();
	}
}

// Called every frame
void APPBossTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

