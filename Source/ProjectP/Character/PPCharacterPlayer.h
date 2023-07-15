// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Character/PPCharacterBase.h"
#include "ProjectP/Interface/StatusInterface.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
#include "ProjectP/Character/PPCharacterStatusData.h"
#include "PPCharacterPlayer.generated.h"


UCLASS()
class PROJECTP_API APPCharacterPlayer : public APPCharacterBase, public IStatusInterface
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
	virtual void SetIdleState() override;
	virtual void SetDeadState() override;
	
	virtual void RecoveryHealth(const float Health) override;
	const virtual float GetCurrentHealth() override;
	const virtual uint8 GetCurrentState() override;
	
	// Player Variable Section
private:
	UPROPERTY(EditAnywhere, Category = DataAsset)
	UPPCharacterStatusData* PlayerStatusData;
	
	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	uint32 PlayerHealth;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	uint32 PlayerRecoveryHealthOnIdle;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float PlayerWalkSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float PlayerRunSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	uint8 PlayerCurrentState;
	
	UPROPERTY(EditAnywhere, Category = CharacterStatus)
	float ReturnToIdleStateTime;
};
