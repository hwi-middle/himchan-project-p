// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "ProjectP/UI/Tutorial/PPTutorialUIWidget.h"
#include "ProjectP/Util/StringDataTable.h"
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
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	void DisplayWidgetContents();
	void HideWidgetBackground();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	void ClearAllTimerOnLevelChange();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> TutorialWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPPTutorialUIWidget> TutorialWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> TutorialWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> TriggerBox;

protected:
	UPROPERTY()
	TObjectPtr<AActor> OverlapActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", DisplayName = "CommanderSoundEvent")
	EEventTriggerType CommanderSoundTriggerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", DisplayName = "CommanderSound")
	TObjectPtr<USoundCue> CommanderSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commander", DisplayName = "CommanderSFXSound")
	TObjectPtr<USoundCue> CommanderSFXSoundCue;
	
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

private:
	UPROPERTY()
	FTimerHandle BackgroundOpacityTimer;

	UPROPERTY()
	FTimerHandle TutorialPanelOpacityTimer;

	UPROPERTY()
	FTimerHandle TurnToPlayerTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundCue> TriggerEnterSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundCue> TriggerOutSoundCue;

	UPROPERTY(EditAnywhere, Category = "TutorialWidget", DisplayName = "Tutorial Info Image")
	TObjectPtr<UTexture2D> TutorialImage;
	
	UPROPERTY(EditAnywhere, Category = "TutorialWidget", DisplayName = "Title")
	FDataTableRowHandle TitleStringDataHandle;
	
	UPROPERTY(EditAnywhere, Category = "TutorialWidget", DisplayName = "Info")
	FDataTableRowHandle InfoStringDataHandle;
};
