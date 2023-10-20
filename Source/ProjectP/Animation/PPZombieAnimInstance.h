// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PPZombieAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FAttackHitCheckStartDelegate)
DECLARE_MULTICAST_DELEGATE(FAttackHitCheckEndDelegate)
DECLARE_MULTICAST_DELEGATE(FAttackAnimEndDelegate)
DECLARE_MULTICAST_DELEGATE(FDeadAnimEndDelegate)
/**
 * 
 */
UCLASS()
class PROJECTP_API UPPZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPPZombieAnimInstance();
	FORCEINLINE void SetAttackBlendValue(float Value) { TrackBlendWithAttackValue = Value; }
	FORCEINLINE void StopAttackBlend() { AnimNotify_AttackHitCheckEnd(); }
	FAttackHitCheckStartDelegate HitCheckStartDelegate;
	FAttackHitCheckEndDelegate HitCheckEndDelegate;
	FAttackAnimEndDelegate AttackAnimEndDelegate;
	FDeadAnimEndDelegate DeadAnimEndDelegate;
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UPPZombieData> OwnerData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float ResearchThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float TrackingThreshold;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float TrackBlendWithAttackValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsTrack : 1;

private:
	UFUNCTION(BlueprintCallable)
	void AnimNotify_AttackHitCheckStart();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_AttackHitCheckEnd();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_AttackAnimEnd();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EnterDeadLoop();
	
	void AnimBlendSequence();
	
private:
	FTimerHandle AnimBlendTimerHandle;

	float TrackToAttackBlendSpeed;
};
