// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ProjectP/Character/PPCharacterZombie.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
#include "BTTask_PPZombieAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_PPZombieAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_PPZombieAttack();
	FAICharacterPatternFinished PatternFinished;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
