// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Enumeration/PPWidgetName.h"
#include "PPLobbyUIBaseActor.generated.h"

UCLASS()
class PROJECTP_API APPLobbyUIBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPLobbyUIBaseActor();
	
	UFUNCTION(BlueprintCallable)
	void ToggleWidgetVisible(EWidgetName WidgetName);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> LobbyWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> SettingWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> TutorialWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> ExitCheckWidgetComponent;
};
