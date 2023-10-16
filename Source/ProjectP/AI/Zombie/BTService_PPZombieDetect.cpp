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
	//TODO: 별도의 플레이어 전용 채널로 변경하기
	FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParams
		);

	if(!bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(KEY_TARGET, nullptr);
		if(OwnerComp.GetBlackboardComponent()->GetValueAsVector(KEY_BASE_LOCATION) != ControllingPawn->GetActorLocation())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(KEY_IS_NOT_LOCATE_SPAWN, true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(KEY_IS_NOT_LOCATE_SPAWN, false);
			ControllingPawn->SetResearchSpeed();
		}
		return;
	}
	
	for (auto const& OverlapResult : OverlapResults)
	{
		APPCharacterPlayer* PlayerCharacter = Cast<APPCharacterPlayer>(OverlapResult.GetActor());
		// ACharacter* PlayerCharacter = Cast<ACharacter>(OverlapResult.GetActor());
		if(PlayerCharacter)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(KEY_TARGET, PlayerCharacter);
			ControllingPawn->SetTrackingSpeed();
			DrawDebugSphere(World, Center, DetectRadius, 32, FColor::Green, false, 0.1f);
			return;
		}
	}
}
