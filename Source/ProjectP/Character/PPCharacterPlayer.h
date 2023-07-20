// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Character/PPCharacterBase.h"
#include "..\Interface\CharacterStatusInterface.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
#include "ProjectP/Character/PPCharacterStatusData.h"
#include "PPCharacterPlayer.generated.h"


UCLASS()
class PROJECTP_API APPCharacterPlayer : public APPCharacterBase, public ICharacterStatusInterface
{
	GENERATED_BODY()
public:
	APPCharacterPlayer();
	// Default Protected Section
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	// StatusInterface override
public:
	virtual void SetupCharacterStatusData(const class UPPCharacterStatusData* CharacterStatusData) override;
	FORCEINLINE virtual void SetCharacterState(const ECharacterState EState) override { CurrentState = EState; }
	FORCEINLINE const virtual ECharacterState GetCurrentState() override { return CurrentState; }

	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }
	
	// Player Variable Section
private:
	UPROPERTY(EditAnywhere, Category = DataAsset)
	TObjectPtr<class UPPCharacterStatusData> PlayerStatusData;
	
	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	uint32 Health;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	uint32 RecoveryHealthOnIdle;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float RunSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	ECharacterState CurrentState;
	
	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float ReturnToIdleStateTime;
};
