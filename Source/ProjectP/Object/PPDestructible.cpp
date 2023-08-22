// Fill out your copyright notice in the Description page of Project Settings.


#include "PPDestructible.h"

#include "Field/FieldSystemComponent.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values for this component's properties
UPPDestructible::UPPDestructible()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//Destroyer = FPPConstructorHelper::FindAndGetObject<UBlueprint>(TEXT("/Script/Engine.Blueprint'/Engine/EditorResources/FieldNodes/FS_MasterField.FS_MasterField'"));
	bIsDestructed = false;
}

// Called when the game starts
void UPPDestructible::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Health = 1.0f;
	AActor* OuterActor = Cast<AActor>(GetOuter());
	OuterActor->Tags.Add(TEXT("DestructibleObject"));
}

void UPPDestructible::IncreaseHealth(const float Value)
{
	Health += Value;
}

void UPPDestructible::DecreaseHealth(const float Value)
{
	Health -= Value;
	if (Health <= 0.f &&  !bIsDestructed)
	{
		UE_LOG(LogTemp, Log, TEXT("Spawn"));
		DestructDelegate.Broadcast();
		bIsDestructed = true;
		//AActor* SpawnedDestroyer = GetWorld()->SpawnActor<AActor>((UClass*)Destroyer->GeneratedClass, GetComponentLocation(), FRotator::ZeroRotator);
		//SpawnedDestroyer->SetActorScale3D(FVector(DestroyerScale));
	}
}
