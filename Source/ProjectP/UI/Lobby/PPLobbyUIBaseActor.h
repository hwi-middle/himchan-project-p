// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "ProjectP/UI/Lobby/PPLobbyUIWidget.h"
#include "ProjectP/Enumeration/PPSubWidgetType.h"
#include "ProjectP/UI/Setting/PPSettingBaseActor.h"
#include "PPLobbyUIBaseActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEntryMainLevelDelegate);

UCLASS()
class PROJECTP_API APPLobbyUIBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPLobbyUIBaseActor();

	UPROPERTY(BlueprintAssignable)
	FEntryMainLevelDelegate EntryMainLevelDelegate;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ClearAllTimerOnLevelChange();
	
protected:
	UFUNCTION(BlueprintCallable)
	void OpenSubWidget(ESubWidgetType SubWidget = ESubWidgetType::None);

	UFUNCTION(BlueprintCallable)
	void ReturnFromSettingToLobby();

	UFUNCTION(BlueprintCallable)
	void EntryMainLevelSequence();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TObjectPtr<UWidgetComponent> LobbyWidgetComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Widget")
	TObjectPtr<UPPLobbyUIWidget> LobbyWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TObjectPtr<UWidgetComponent> ExitWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TObjectPtr<UChildActorComponent> SettingWidgetActor;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Widget")
	TObjectPtr<APPSettingBaseActor> SettingWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundCue> WidgetMoveSoundCue;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	float WidgetAnimationTick;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	float WidgetAnimationMoveValue;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	float WidgetMaximumMovementAmount;

	UPROPERTY(EditDefaultsOnly,Category = "Widget")
	float LobbyWidgetMaximumHeight;
	
	UPROPERTY()
	FVector CurrentLocation;
	
	UPROPERTY()
	FTimerHandle WidgetAnimationTimer;

	UPROPERTY()
	FTimerHandle EntryMainLevelAnimationTimer;
};
