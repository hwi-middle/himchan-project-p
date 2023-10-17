// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPEventReceiver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventReceivingDelegate);

UCLASS()
class PROJECTP_API APPEventReceiver : public AActor
{
	GENERATED_BODY()

public:	
	APPEventReceiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void AddEventStack();
	
	UPROPERTY(BlueprintAssignable)
	FEventReceivingDelegate EventReceivingDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActivationEventStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentEventStack;
};
