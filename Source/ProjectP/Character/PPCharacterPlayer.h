// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Character/PPCharacterBase.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
#include "ProjectP/Character/PPPlayerStatusData.h"
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

	// StatusInterface override
protected:
	virtual void SetupCharacterStatusData(const class UDataAsset* CharacterStatusData) override;
	FORCEINLINE virtual void SetCharacterState(const ECharacterState EState) override { CurrentState = EState; }
	FORCEINLINE const virtual ECharacterState GetCurrentState() override { return CurrentState; }

	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }
	
	// Player Variable Section
private:
	UPROPERTY(VisibleAnywhere, Category = DataAsset)
	UPPPlayerStatusData* PlayerStatusData;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 Health;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 Infection;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 MaximumInfection;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 RecoveryHealthValueOnIdle;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	ECharacterState CurrentState;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float ReturnToIdleStateTime;

private:

};
