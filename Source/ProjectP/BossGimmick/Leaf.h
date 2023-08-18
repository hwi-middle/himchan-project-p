// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "Sound/SoundCue.h"
#include "Leaf.generated.h"

UCLASS()
class PROJECTP_API ALeaf : public AActor, public ICharacterStatusInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALeaf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ClearAllTimerOnLevelChange();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//	FORCEINLINE void SetTarget(AActor* InTarget) { Target = InTarget; }
	//void Init(AActor* Player, float Damage);

	void StartTracing();
	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	const virtual float GetCurrentHealth() override { return Health; }

private:
	void BlinkAndExplode();
	bool CheckPlayerWithSphere(float InRadius, FHitResult& Result);
	void FadeOutAndDestroy();

private:
	UPROPERTY()
	float Health;

	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY()
	TObjectPtr<class UPPBossGimmickData> BossGimmickData;

	UPROPERTY()
	TObjectPtr<AActor> Target;

	UPROPERTY()
	float Damage;

	UPROPERTY()
	float MoveSpeed;

	UPROPERTY()
	float RotateSpeed;

	UPROPERTY()
	float TraceStartDelay;

	UPROPERTY()
	float ElapsedTraceTime;

	UPROPERTY()
	float TraceDuration;

	UPROPERTY()
	float CurrentBlinkSpeed;

	UPROPERTY()
	float MaxBlinkSpeed;

	UPROPERTY()
	float BlinkDuration;

	UPROPERTY()
	float ElapsedBlinkTime;

	UPROPERTY()
	float FadeOutDuration;

	UPROPERTY()
	float ElapsedFadeOutTime;
	
	UPROPERTY()
	uint32 bIsActivated : 1;

	UPROPERTY()
	FTimerHandle DelayTracingTimerHandle;

	UPROPERTY()
	FTimerHandle BlinkTimerHandle;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

	UPROPERTY()
	FTimerHandle DestroyEffectTimerHandle;
	
	UPROPERTY()
	TObjectPtr<USoundCue> ExplodeSoundCue;

	UPROPERTY()
	TObjectPtr<USoundCue> DestroySoundCue;
};
