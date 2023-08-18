// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "ProjectP/UI/Tutorial/PPTutorialUIWidget.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Enumeration/EventTriggerType.h"
#include "Sound/SoundCue.h"
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

	void DisplayWidgetContents();
	void HideWidgetBackground();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> TutorialWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPPTutorialUIWidget> TutorialWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> TutorialWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY()
	TObjectPtr<AActor> OverlapActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", DisplayName = "CommanderSoundEvent")
	EEventTriggerType CommanderSoundTriggerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", DisplayName = "CommanderSound")
	TObjectPtr<USoundCue> CommanderSoundCue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetHalfWidthValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetWidthAddValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetOpacityAddValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetAnimationTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetRotateDelay;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FTimerHandle BackgroundOpacityTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FTimerHandle GuidePanelOpacityTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FTimerHandle TurnToPlayerTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundCue> TriggerEnterSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundCue> TriggerOutSoundCue;
	
};
