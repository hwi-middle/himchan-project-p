// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "ProjectP/Enumeration/PPCharacterState.h"
#include "ProjectP/Character/PPPlayerStatusData.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/PostProcessVolume.h"
#include "ProjectP/Player/PPVRPawn.h"
#include "PPCharacterPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadAnotherLevelDelegate);

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

private:
	void ClearAllTimerOnLevelChanged();
	
public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	FORCEINLINE const virtual float GetCurrentHealth() override { return Health; }
	
	UFUNCTION()
	FORCEINLINE UAudioComponent* GetAudioComponent() { return AudioComponent; }
	
	UFUNCTION()
	FORCEINLINE UAudioComponent* GetCommanderAudioComponent() { return CommanderAudioComponent; }
	
	UPROPERTY(BlueprintAssignable)
	FLoadAnotherLevelDelegate LoadAnotherLevelDelegate;
	
	// StatusInterface override
protected:
	virtual void SetupCharacterStatusData(UDataAsset* CharacterStatusData);
//	FORCEINLINE virtual void SetCharacterState(const ECharacterState EState) override { CurrentState = EState; }
//	FORCEINLINE const virtual ECharacterState GetCurrentState() override { return CurrentState; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = Collision)
	TObjectPtr<UCapsuleComponent> CollisionCapsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAudioComponent> CommanderAudioComponent;
	
	// Player Variable Section
private:
	UPROPERTY(VisibleAnywhere, Category = DataAsset)
	TObjectPtr<UPPPlayerStatusData> PlayerStatusData;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 LowHealthWarningValue;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	uint32 RecoveryHealthAmountPerSecond;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	FTimerHandle RecoveryTickTimer;
	
	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	float ReturnToIdleStateTime;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	FTimerHandle HitCheckTimer;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	FTimerHandle DamageFXFadeTimer;

	UPROPERTY(EditDefaultsOnly, Category = CharacterStatus)
	FTimerHandle LowHealthWarningTimer;

	UPROPERTY(EditDefaultsOnly)
	FTimerHandle LevelRestartTimer;

	UPROPERTY(EditDefaultsOnly)
	FTimerHandle LevelStartTimer;
	
	UPROPERTY()
	TObjectPtr<APostProcessVolume> PostProcessVolume;
	
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialInstance;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USoundCue> HitSoundCue;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USoundCue> CommanderHealthWaringSoundCue;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USoundCue> LowHealthSoundCue;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USoundCue> DeadSoundCue;
	
	UPROPERTY()
	float DamageFXIntensity;
	
	UPROPERTY()
	float ElapsedDamageFXFadeTime;
	
	UPROPERTY()
	float DamageFXFadeInDuration;
	
	UPROPERTY()
	float DamageFXFadeOutDuration;

	UPROPERTY()
	float SavedExposureValue;
	
	UPROPERTY()
	float SavedVignetteValue;

private:
	UPROPERTY()
	float TargetExposureBias;
	
	UPROPERTY()
	float TargetVignetteIntensity;

	UPROPERTY()
	float AddExposureBias;

	UPROPERTY()
	float AddVignetteIntensity;
	
private:
	void RestartLevelSequence();
	void EnableLowHealthWarning();
	void EnableHitCheckTimer();
	void EnableRecoveryHealthTimer();
	void ShowDamageFX();

private:
	void RestartLevelDelegate();
	void EnableLowHealthWarningDelegate();
	void EnableHitCheckTimerDelegate();
	void EnableRecoveryHealthTimerDelegate();
	void ShowDamageFXDelegate();
};
