// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PPZombieFindLocation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_PPZombieFindLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PPZombieFindLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
};
