// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPEventReceiver.h"
#include "Components/SceneComponent.h"
#include "PPEventCaller.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTP_API UPPEventCaller : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPPEventCaller();
	
	FORCEINLINE void DeliverEvent() const { EventReceiver->AddEventStack(); }
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<APPEventReceiver> EventReceiver;
};
