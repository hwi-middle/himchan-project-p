// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/AI/Zombie/BTService_PPZombieDetect.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Character/PPCharacterZombie.h"
#include "ProjectP/Constant/PPBlackBoardKeyName.h"

UBTService_PPZombieDetect::UBTService_PPZombieDetect()
{
	NodeName = TEXT("Detect Target");
	Interval = 1.0f;
}

void UBTService_PPZombieDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APPCharacterZombie* ControllingPawn = Cast<APPCharacterZombie>(OwnerComp.GetAIOwner()->GetPawn());
	if(!ControllingPawn)
	{
		return;
	}
	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if(!World)
	{
		return;
	}
	
	float DetectRadius = ControllingPawn->GetAIMissingTargetRadius();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParams
		);
	
	bool bIsPlayerDetect = false;
	if(bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			// APPCharacterPlayer* PlayerCharacter = Cast<APPCharacterPlayer>(OverlapResult.GetActor());
			ACharacter* PlayerCharacter = Cast<ACharacter>(OverlapResult.GetActor());
			if(PlayerCharacter)
			{
				bIsPlayerDetect = true;
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(KEY_TARGET, PlayerCharacter);
				DrawDebugSphere(World, Center, DetectRadius, 32, FColor::Green, false, 0.1f);
				// DrawDebugPoint(World, PlayerCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 1.0f);
				// DrawDebugLine(World, ControllingPawn->GetActorLocation(), PlayerCharacter->GetActorLocation(), FColor::Red, false, 1.0f);
			}
		}
	}
	if(!bIsPlayerDetect)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(KEY_TARGET, nullptr);
		if(OwnerComp.GetBlackboardComponent()->GetValueAsVector(KEY_BASE_LOCATION) != ControllingPawn->GetActorLocation())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(KEY_IS_NOT_LOCATE_SPAWN, true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(KEY_IS_NOT_LOCATE_SPAWN, false);
		}
	} 
}
