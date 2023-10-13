// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPZombieData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPZombieData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Mesh, DisplayName = "좀비 메시")
	TObjectPtr<USkeletalMesh> ZombieMesh;

	UPROPERTY(EditAnywhere, Category = Mesh, DisplayName = "좀비 애님 몽타주")
	TObjectPtr<UAnimMontage> ZombieAnimMontage;
	
public:
	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "좀비 체력");
	float Health;

	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "좀비 공격력");
	float AttackDamage;

	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "좀비 공격 체크 범위");
	float AttackRange;
	
	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "좀비 공격 히트 체크 범위(박스)");
	FVector AttackHitCheckBox;
	
	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "좀비 탐색 상태 이동속도");
	float ResearchMoveSpeed;

	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "좀비 추적 상태 이동속도");
	float TrackingMoveSpeed;

	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "사망 후 자동 소멸 시간");
	float AutoDestroyTime;
	
public:
	UPROPERTY(EditAnywhere, Category = Anim, DisplayName = "좀비 걷기 <-> 탐색 애니메이션 전환 요구 속도");
	float ResearchThreshold;

	UPROPERTY(EditAnywhere, Category = Anim, DisplayName = "좀비 탐색 <-> 추적 애니메이션 전환 요구 속도");
	float TrackingThreshold;

	UPROPERTY(EditAnywhere, Category = Anim, DisplayName = "좀비 추적 -> 공격 애니메이션 블렌딩 속도");
	float TrackToAttackBlendSpeed;
	
public:
	UPROPERTY(EditAnywhere, Category = AI, DisplayName = "정찰 범위(반지름)")
	float PatrolRadius;
	
	UPROPERTY(EditAnywhere, Category = AI, DisplayName = "탐지 범위(반지름)")
	float DetectRadius;

	UPROPERTY(EditAnywhere, Category = AI, DisplayName = "추적 해제 범위(반지름)")
	float MissingTargetRadius;
	
	UPROPERTY(EditAnywhere, Category = AI, DisplayName = "시야 각도(도)")
	float DetectDegrees;
	
};
