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
	
	UPROPERTY(EditAnywhere, Category = Status, DisplayName = "좀비 이동속도");
	float MoveSpeed;
	
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
