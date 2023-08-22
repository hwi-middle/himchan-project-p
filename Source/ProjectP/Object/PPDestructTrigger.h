// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPDestructible.h"
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
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void AddTriggerStack();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DestructTrigger")
	int32 MaximumTriggerStack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurrentTriggerStack;
	
};
