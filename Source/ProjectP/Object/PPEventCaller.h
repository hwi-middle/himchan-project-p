// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PPEventCaller.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventDeliverDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTP_API UPPEventCaller : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPPEventCaller();

	UPROPERTY(BlueprintAssignable)
	FEventDeliverDelegate EventDeliverDelegate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FORCEINLINE void DeliverEvent() const { EventDeliverDelegate.Broadcast(); }
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
