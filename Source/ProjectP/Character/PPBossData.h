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
// CharacterStatusData를 상속받긴 하는데 기획상에선 실질적으로 체력 외에는 사용 목적 애매해서 고민중
class PROJECTP_API UPPBossData : public UPPCharacterStatusData
{
	GENERATED_BODY()
public:
	UPPBossData();
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	TMap<EBossPattern, uint32> PatternDamages;

	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	float GenerateWeakPointTime;

	// 약점 파괴 횟수 체크
	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	uint32 RequiredWeakPointDestructionCount;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterGimmick)
	float NeutralizeTime;
	
};
