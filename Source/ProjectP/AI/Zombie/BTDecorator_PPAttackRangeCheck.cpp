// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/AI/Zombie/BTDecorator_PPAttackRangeCheck.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectP/Character/PPCharacterZombie.h"
#include "ProjectP/Constant/PPBlackBoardKeyName.h"

UBTDecorator_PPAttackRangeCheck::UBTDecorator_PPAttackRangeCheck()
{
}

bool UBTDecorator_PPAttackRangeCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	APPCharacterZombie* ControllingPawn = Cast<APPCharacterZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if(!ControllingPawn)
	{
		return false;
	}
	
	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if(!World)
	{
		return false; 
	}

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(KEY_TARGET));
	if(TargetActor)
	{
		float TargetDistance = ControllingPawn->GetDistanceTo(TargetActor);
		return TargetDistance <= ControllingPawn->GetAIAttackRange();
	}
	return false;
}
