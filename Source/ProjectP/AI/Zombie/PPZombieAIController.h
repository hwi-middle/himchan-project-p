// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ProjectP/Character/PPZombieData.h"
#include "ProjectP/Constant/PPBlackBoardKeyName.h"
#include "PPZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APPZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	APPZombieAIController();

	void ActivateAI();
	void DeActivateAI();
	FORCEINLINE AActor* GetTargetActor() { return Cast<AActor>(Blackboard->GetValueAsObject(KEY_TARGET)); }
	
	UFUNCTION()
	void SetTarget(const TArray<AActor*>& Actors);
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	TObjectPtr<UBlackboardData> CommonBlackboardData;

	UPROPERTY()
	TObjectPtr<UBehaviorTree> CommonBehaviorTree;

	UPROPERTY()
	TObjectPtr<UAIPerceptionComponent> CommonPerceptionComp;

	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> CommonSight;

	UPROPERTY()
	TObjectPtr<UPPZombieData> ZombieAIData;
};
