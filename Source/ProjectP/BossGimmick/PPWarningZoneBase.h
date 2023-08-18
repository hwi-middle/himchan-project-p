// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPWarningZoneBase.generated.h"

UCLASS()
class PROJECTP_API APPWarningZoneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPWarningZoneBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ClearAllTimerOnLevelChange();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY()
	float Opacity;

	UPROPERTY()
	float Duration;

public:
	void Show(float InDuration);
	void HideAndDestroy(float InDuration);
	
private:
	UPROPERTY()
	float Alpha;
	
protected:
	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY()
	FTimerHandle FadeTimerHandle;

	UPROPERTY()
	float FadeTimerRate;
};
