// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPEventCaller.h"
#include "GameFramework/Actor.h"
#include "PPEventTestActor.generated.h"

UCLASS()
class PROJECTP_API APPEventTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPEventTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPPEventCaller> EventCallerComponent;
};
