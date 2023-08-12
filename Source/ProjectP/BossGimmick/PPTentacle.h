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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<class APPWarningZoneCylinder> WarningZone;

	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> TentacleMesh;

public:
	void ShowWarningSign();
	void HideWarningSignAndAttack();
};
