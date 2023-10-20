// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectP/Animation/PPZombieAnimInstance.h"
#include "ProjectP/Character/PPZombieData.h"
#include "ProjectP/Character/PPCharacterEnemy.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
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
	FAICharacterPatternFinished PatternFinishedDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginDestroy() override;
	void SetDeadLoop();
	void DestroyThis();

	// AI 호출
	// AI 관련 클래스에서만 호출 가능하게 인자값으로 적절하게 무언가를 받는 방법을 고민하는 중이에요
public:
	void SetAIPatternDelegate(const FAICharacterPatternFinished& FinishedDelegate);
	UFUNCTION()
	void PlayPatternAnimMontage();
	FORCEINLINE float GetHp() { return Health; }
	FORCEINLINE float GetAIAttackRange() { return AttackRange; }
	FORCEINLINE float GetAIPatrolRadius() { return PatrolRadius; }
	FORCEINLINE float GetAIDetectRadius() { return DetectRadius; }
	FORCEINLINE float GetAIMissingTargetRadius() { return MissingTargetRadius; }
	FORCEINLINE float GetAIDetectDegrees() { return DetectDegrees; }
	FORCEINLINE void SetNewState(ECharacterState State) { CurrentState = State; }
	FORCEINLINE void SetResearchSpeed() { GetCharacterMovement()->MaxWalkSpeed = ResearchSpeed; }
	FORCEINLINE void SetTrackingSpeed() { GetCharacterMovement()->MaxWalkSpeed = TrackingSpeed; }

	// 인터페이스 구현
public:
	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	FORCEINLINE const virtual float GetCurrentHealth() override { Super::GetCurrentHealth(); return Health; }

	// 공격 관련 함수
private:
	void CheckAttackHitResult();
	// 애님 노티파이 연결
	UFUNCTION()
	void AttackHitCheckStart();
	UFUNCTION()
	void AttackHitCheckEnd();

	// 공격 애님 노티파이 종료시 호출
	UFUNCTION()
	void AttackFinishedNotify();

	// 공격 관련 변수
private:
	FTimerHandle AttackHitCheckTimerHandle;

	float AttackRange;

	float AttackDamage;

	FVector AttackHitCheckBox;

	uint8 bIsDamageCaused : 1;

	// AI 관련 변수
private:
	float Health;

	float PatrolRadius;

	float DetectRadius;

	float MissingTargetRadius;

	float DetectDegrees;

	float ResearchSpeed;

	float TrackingSpeed;

	ECharacterState CurrentState;

	// 죽음 애니메이션 관련 변수
private:
	FTimerHandle DeadTimerHandle;

	float AutoDestroyTime;
	
private:
	UPROPERTY()
	TObjectPtr<UPPZombieData> ZombieData;

	UPROPERTY()
	TObjectPtr<UAnimMontage> ZombieAnimMontage;

	UPROPERTY()
	TObjectPtr<UPPZombieAnimInstance> ZombieAnimInstance;
};
