// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Character/PPZombieData.h"
#include "ProjectP/Character/PPCharacterEnemy.h"
#include "PPCharacterZombie.generated.h"

DECLARE_MULTICAST_DELEGATE(FAICharacterPatternFinished)
/**
 * 
 */
UCLASS()
class PROJECTP_API APPCharacterZombie : public APPCharacterEnemy
{
	GENERATED_BODY()

public:
	APPCharacterZombie();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginDestroy() override;
	void Attack();
	void SetDead();
	
	// AI 호출
public:
	void SetAIPatternDelegate(FAICharacterPatternFinished FinishedDelegate);
	void PlayPatternAnimMontage();
	FORCEINLINE float GetHp() { return Health; }
	FORCEINLINE float GetAIPatrolRadius() { return PatrolRadius; }
	FORCEINLINE float GetAIDetectRadius() { return DetectRadius; }
	FORCEINLINE float GetAIMissingTargetRadius() { return MissingTargetRadius; }
	FORCEINLINE float GetAIDetectDegrees() { return DetectDegrees; }
	

	// 공격 관련 변수
private:
	void CheckAttackResult();
	void AttackFinishedNotify(UAnimMontage* Montage, bool IsInterrupted);
	
	// AI 관련 변수
private:
	FAICharacterPatternFinished PatternFinishedDelegate;

	float Health;
	
	float PatrolRadius;

	float DetectRadius;

	float MissingTargetRadius;
	
	float DetectDegrees;
	
private:
	UPROPERTY()
	TObjectPtr<UPPZombieData> ZombieData;

	UPROPERTY()
	TObjectPtr<UAnimMontage> ZombieAnimMontage;
};
