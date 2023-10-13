// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/AI/Zombie/BTTask_PPZombieAttack.h"

#include "AIController.h"
#include "PPZombieAIController.h"
#include "ProjectP/Character/PPCharacterZombie.h"

UBTTask_PPZombieAttack::UBTTask_PPZombieAttack()
{
	
}

EBTNodeResult::Type UBTTask_PPZombieAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	APPCharacterZombie* ControllingPawn = Cast<APPCharacterZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if(!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterPatternFinished PatternFinished;
	PatternFinished.AddLambda([&]()
	{
		ControllingPawn->SetNewState(ECharacterState::Tracking);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	});
	
	ControllingPawn->SetAIPatternDelegate(PatternFinished);
	ControllingPawn->PlayPatternAnimMontage(ECharacterState::Attack);
	return EBTNodeResult::InProgress;
}
