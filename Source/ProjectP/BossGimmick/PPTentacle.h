// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPTentacle.generated.h"

UCLASS()
class PROJECTP_API APPTentacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPTentacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ClearAllTimerOnLevelChange();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<class UPPBossGimmickData> BossGimmickData;

	UPROPERTY()
	TObjectPtr<class UPPTentacleAnimInstance> AnimInstance;
	
	UPROPERTY()
	TObjectPtr<class APPWarningZoneCylinder> WarningZone;

	UPROPERTY(EditDefaultsOnly, Category = VineGardenData)
	TObjectPtr<class USkeletalMeshComponent> TentacleMesh;

	UPROPERTY()
	FTimerHandle WarningTimerHandle;

	UPROPERTY()
	FTimerHandle HitPlayerTimerHandle;

	UPROPERTY()
	float WarningFadeInDuration;
	
	UPROPERTY()
	float WarningFadeOutDuration;

	UPROPERTY()
	float WarningDuration;
	
	UPROPERTY()
	float Damage;

	UPROPERTY()
	float DamageRadius;
	
	UPROPERTY()
	TObjectPtr<class APPCharacterBoss> Boss;
	
public:
	void ShowWarningSign();
	FORCEINLINE void SetBoss(class APPCharacterBoss* InBoss) { Boss = InBoss; }

private:
	void HideWarningSignAndAttack();
	void HideTentacle();
	void DestroyTentacle();

private:
	void ShowWarningSignDelegate();
	void HideWarningSignAndAttackDelegate();
	void HideTentacleDelegate();
	void DestroyTentacleDelegate();
};
