// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "ProjectP/Interface/CharacterStatusInterface.h"
#include "PPBossCore.generated.h"

UCLASS()
class PROJECTP_API APPBossCore : public AActor, public ICharacterStatusInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APPBossCore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<class UPPWeaponData> PrimaryWeaponData;
	
	UPROPERTY()
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> AdditionalCollision;

	UPROPERTY()
	TObjectPtr<class UAnimSequence> Anim;

	UPROPERTY()
	TObjectPtr<class APPCharacterBoss> Boss;

public:
	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	const virtual float GetCurrentHealth() override { return Health; }
	void SetAdditionalCollisionEnable(const bool Value);
	FORCEINLINE void SetBoss(APPCharacterBoss* InBoss) { Boss = InBoss; }
};
