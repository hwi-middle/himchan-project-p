// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/PostProcessVolume.h"
#include "GameFramework/Actor.h"
#include "PPSceneLoadTriggerActor.generated.h"

UCLASS()
class PROJECTP_API APPSceneLoadTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPSceneLoadTriggerActor();
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	void LoadLevelSequence();
	
private:
	void LoadLevelDelegate();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> TriggerBox;
	
private:
	UPROPERTY()
	TObjectPtr<APostProcessVolume> PostProcessVolume;
	
	UPROPERTY(EditAnywhere, DisplayName = "페이드 아웃 목표 노출 값(-)")
	float TargetExposureBias;
	
	UPROPERTY(EditAnywhere, DisplayName = "페이드 아웃 목표 비네트 값(+)")
	float TargetVignetteIntensity;

	UPROPERTY(EditAnywhere, DisplayName = "페이드 아웃 프레임당 노출 감소 값")
	float AddExposureBias;

	UPROPERTY(EditAnywhere, DisplayName = "페이드 아웃 프레임당 비네트 증가 값")
	float AddVignetteIntensity;
	
};
