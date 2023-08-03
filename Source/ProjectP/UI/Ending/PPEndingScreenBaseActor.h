// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectP/UI/Ending/PPEndingUIWidget.h"
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

	void FadeInOrOutScreenImage(const bool IsFaded);
	void VisibleCreditPanel();
	void MoveCreditPanel();
	void EnableAutoFadeTimer();
	void EnableLight();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WidgetCompoent)
	TObjectPtr<UWidgetComponent> EndingScreenWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WidgetCompoent)
	TObjectPtr<UPPEndingUIWidget> EndingUIWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WidgetCompoent)
	TObjectPtr<USpotLightComponent> ScreenLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AutoFadeTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ImageFadeSequenceTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxCreditBottomPosition;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CreditAddPositionValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LightMaxIntensity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LightEnhanceIntensityPerTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimerTick;
	
	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle FadeSequenceTimer;

	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle CreditMoveTimer;
	
	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle AutoFadeDelayTimer;

	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle LightIntensityControlTimer;
	
};
