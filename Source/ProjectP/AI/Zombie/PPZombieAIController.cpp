// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/AI/Zombie/PPZombieAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Character/PPCharacterZombie.h"
#include "ProjectP/Constant/PPBlackBoardKeyName.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"

APPZombieAIController::APPZombieAIController()
{
	CommonBlackboardData = FPPConstructorHelper::FindAndGetObject<UBlackboardData>(TEXT("/Script/AIModule.BlackboardData'/Game/186-ZombieAI/AI/BB_Zombie.BB_Zombie'"), EAssertionLevel::Check);
	CommonBehaviorTree = FPPConstructorHelper::FindAndGetObject<UBehaviorTree>(TEXT("/Script/AIModule.BehaviorTree'/Game/186-ZombieAI/AI/BT_Zombie.BT_Zombie'"), EAssertionLevel::Check);
	ZombieAIData = FPPConstructorHelper::FindAndGetObject<UPPZombieData>(TEXT("/Script/ProjectP.PPZombieData'/Game/186-ZombieAI/ZombieData.ZombieData'"), EAssertionLevel::Check);
	
	CommonPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPercptionComponent"));
	CommonSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI_Sight"));
	
	CommonSight->SightRadius = ZombieAIData->DetectRadius;
	CommonSight->LoseSightRadius = ZombieAIData->MissingTargetRadius;
	CommonSight->PeripheralVisionAngleDegrees = ZombieAIData->DetectDegrees;
	
	CommonSight->DetectionByAffiliation.bDetectEnemies = true;
	CommonSight->DetectionByAffiliation.bDetectFriendlies = true;
	CommonSight->DetectionByAffiliation.bDetectNeutrals = true;
	CommonSight->SetMaxAge(0.05f);
	
	CommonPerceptionComp->ConfigureSense(*CommonSight);
	CommonPerceptionComp->SetDominantSense(CommonSight->GetSenseImplementation());
	CommonPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &APPZombieAIController::SetTarget);
}

void APPZombieAIController::ActivateAI()
{
	UBlackboardComponent* BlackboardComponent = Blackboard.Get();
	if(UseBlackboard(CommonBlackboardData, BlackboardComponent))
	{
		Blackboard->SetValueAsVector(KEY_BASE_LOCATION, GetPawn()->GetActorLocation());
		
		bool RunResult = RunBehaviorTree(CommonBehaviorTree);
		ensure(RunResult);
	}
}

void APPZombieAIController::DeActivateAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree();
	}
}

void APPZombieAIController::SetTarget(const TArray<AActor*>& Actors)
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	for(AActor* DetectActor : Actors)
	{
		FActorPerceptionBlueprintInfo PerceptionInfo;
		PerceptionComponent->GetActorsPerception(DetectActor, PerceptionInfo);
		APPCharacterPlayer* PlayerCharacter = Cast<APPCharacterPlayer>(DetectActor);
		if(PlayerCharacter)
		{
			if(!Blackboard->GetValueAsObject(KEY_TARGET))
			{
				Blackboard->SetValueAsObject(KEY_TARGET, PlayerCharacter);
				TArray<FHitResult> HitResults;
				FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(Detect), false, GetPawn());
				bool bResult = GetWorld()->SweepMultiByChannel(
					HitResults,
					GetPawn()->GetActorLocation(),
					GetPawn()->GetActorLocation(),
					FQuat::Identity,
					ECC_PLAYER_ATTACK,
					FCollisionShape::MakeSphere(CommonSight->SightRadius),
					CollisionQueryParams
					);
				if (bResult)
				{
					for(auto Result : HitResults)
					{
						APPCharacterZombie* FriendZombie = Cast<APPCharacterZombie>(Result.GetActor());
						if(FriendZombie)
						{
							APPZombieAIController* FriendController = Cast<APPZombieAIController>(FriendZombie->GetController());
							if(FriendController)
							{
								FriendController->SetTarget(Actors);
								
							}
						}
					}
				}
			}
			return;
		}
	}
}

void APPZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ActivateAI();

	APPCharacterZombie* ControllingPawn = Cast<APPCharacterZombie>(InPawn);
	check(ControllingPawn);
}
