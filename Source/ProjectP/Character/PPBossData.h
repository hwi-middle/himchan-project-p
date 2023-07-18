// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectP/AI/Boss/PPBossAIController.h"
#include "ProjectP/Character/PPCharacterStatusData.h"
#include "ProjectP/Enumeration/PPBossPattern.h"
#include "PPBossData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPBossData : public UPPCharacterStatusData
{
	GENERATED_BODY()
public:
	UPPBossData();
	
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimBlueprint* AnimationBP;

	UPROPERTY(EditDefaultsOnly, Category = AIController)
	APPBossAIController* Controller;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	TMap<EBossPattern ,uint32> PattenDamages;

	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	float GenerateWeakPointTime;

	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	uint32 WeakPointDestructionRequired;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	float StunTime;
	
};
