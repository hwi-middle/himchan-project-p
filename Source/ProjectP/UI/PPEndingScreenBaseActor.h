// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "PPEndingScreenBaseActor.generated.h"

UCLASS()
class PROJECTP_API APPEndingScreenBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPEndingScreenBaseActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = WidgetCompoent)
	TObjectPtr<UWidgetComponent> EndingScreenWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly)
	float ImageFadeTime;
	
	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle FadeSequenceTimer;

	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle AutoFadeDelayTimer;
	
};
