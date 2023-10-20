// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/AI/Zombie/BTTask_PPZombieFindLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ProjectP/Character/PPCharacterZombie.h"
#include "ProjectP/Constant/PPBlackBoardKeyName.h"
#include "ProjectP/Game/PPGameInstance.h"


UBTTask_PPZombieFindLocation::UBTTask_PPZombieFindLocation()
{
	
}

EBTNodeResult::Type UBTTask_PPZombieFindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	APPCharacterZombie* ControllingPawn = Cast<APPCharacterZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if(!ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if(!NavSystem)
	{
		return EBTNodeResult::Failed;
	}
	
	const FVector OriginLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(KEY_BASE_LOCATION);
	float PatrolRadius = ControllingPawn->GetAIPatrolRadius();
	
	FNavLocation NextPatrolLocation;
	
	if(NavSystem->GetRandomPointInNavigableRadius(OriginLocation, PatrolRadius, NextPatrolLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(KEY_PATROL_LOCATION, NextPatrolLocation.Location);
		UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
		UGameplayStatics::PlaySound2D(GetWorld(), GameInstance->GetSoundData()->ZombieResearchSoundCue);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
