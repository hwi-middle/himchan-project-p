// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPPauseWidget.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "ProjectP/Enumeration/PPSubWidgetType.h"
#include "ProjectP/UI/Setting/PPSettingBaseActor.h"
#include "PPPauseWidgetActor.generated.h"

UCLASS()
class PROJECTP_API APPPauseWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPPauseWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ClearAllTimerOnLevelChange();
	
protected:
	UFUNCTION(BlueprintCallable)
	void ResumeGame();
	
 	UFUNCTION(BlueprintCallable)
	void OpenSubWidget(ESubWidgetType SubWidget = ESubWidgetType::None);

	UFUNCTION(BlueprintCallable)
	void ReturnFromSettingToPause();

	UFUNCTION(BlueprintCallable)
	void EntryLobbyLevel();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TObjectPtr<UWidgetComponent> PauseWidgetComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Widget")
	TObjectPtr<UPPPauseWidget> PauseWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TObjectPtr<UChildActorComponent> SettingWidgetActor;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Widget")
	TObjectPtr<APPSettingBaseActor> SettingWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	float WidgetMaximumMovementAmount;

	UPROPERTY()
	FTimerHandle EntryLobbyLevelAnimationTimer;
};
