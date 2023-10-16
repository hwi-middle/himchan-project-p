// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_PPZombieDetect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTService_PPZombieDetect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_PPZombieDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
