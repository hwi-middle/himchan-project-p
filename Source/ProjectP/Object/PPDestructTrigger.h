// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PPDestructTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestructTriggerDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTP_API UPPDestructTrigger : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPPDestructTrigger();

	UPROPERTY(BlueprintAssignable)
	FDestructTriggerDelegate DestructTriggerDelegate;

	UFUNCTION(BlueprintCallable)
	void AddTriggerStack();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "DestructTrigger")
	uint32 MaximumTriggerStack;

	UPROPERTY(VisibleAnywhere)
	uint32 CurrentTriggerStack;
	
};
