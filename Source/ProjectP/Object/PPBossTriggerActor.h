// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPEventReceiver.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "PPBossTriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBossEnableDelegate);

UCLASS()
class PROJECTP_API APPBossTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPBossTriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, DisplayName = "활성화할 보스 타겟")
	TObjectPtr<APPCharacterBoss> TargetBoss;

	UPROPERTY(EditAnywhere, DisplayName = "닫으려는 문 타겟")
	TObjectPtr<APPEventReceiver> TargetReceiver;
	
};
