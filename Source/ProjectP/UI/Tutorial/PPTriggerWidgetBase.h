// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "ProjectP/UI/Tutorial/PPTutorialUIWidget.h"
#include "GameFramework/Actor.h"
#include "PPTriggerWidgetBase.generated.h"

UCLASS()
class PROJECTP_API APPTriggerWidgetBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPTriggerWidgetBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> TutorialWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPPTutorialUIWidget> TutorialWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> TriggerBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetOpacityAddValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetAnimationTick;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FTimerHandle WidgetAnimationTimer;
};
