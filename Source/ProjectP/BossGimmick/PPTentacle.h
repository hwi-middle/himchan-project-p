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

public:
	void ShowWarningSign();

private:
	void HideWarningSignAndAttack();
};
