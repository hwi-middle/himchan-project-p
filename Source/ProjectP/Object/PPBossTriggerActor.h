// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PPBossTriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBossEnableDelegate);

UCLASS()
class PROJECTP_API APPBossTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPBossTriggerActor();

	UPROPERTY(BlueprintAssignable)
	FBossEnableDelegate BossEnableDelegate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> TriggerBox;
};
