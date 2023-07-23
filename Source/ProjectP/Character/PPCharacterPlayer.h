// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
#include "ProjectP/Character/PPPlayerStatusData.h"
#include "Components/CapsuleComponent.h"
#include "ProjectP/Player/PPVRPawn.h"
#include "PPCharacterPlayer.generated.h"


UCLASS()
class PROJECTP_API APPCharacterPlayer : public APPVRPawn, public ICharacterStatusInterface
{
	GENERATED_BODY()
public:
	APPCharacterPlayer();
	// Default Protected Section
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	
	// StatusInterface override
protected:
	virtual void SetupCharacterStatusData(UDataAsset* CharacterStatusData) override;
	FORCEINLINE virtual void SetCharacterState(const ECharacterState EState) override { CurrentState = EState; }
	FORCEINLINE const virtual ECharacterState GetCurrentState() override { return CurrentState; }

	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }

private:
	UPROPERTY(EditDefaultsOnly, Category = Collision)
	TObjectPtr<UCapsuleComponent> CollisionCapsule;

	
	// Player Variable Section
private:
	UPROPERTY(VisibleAnywhere, Category = DataAsset)
	TObjectPtr<UPPPlayerStatusData> PlayerStatusData;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 Health;
	
	/* 감염 게이지는 일단은 선언만 해놓고 사용 여부는 기획 파트와 상의 필요
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 InfectionGauge;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 MaximumInfectionValue;
	*/
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 RecoveryHealthAmountOnIdle;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float RecoveryHealthTick;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	FTimerHandle RecoveryTickTimer;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	ECharacterState CurrentState;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float ReturnToIdleStateTime;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	FTimerHandle HitCheckTimer;

private:
	void EnableRecoveryHealthTimer();
};
