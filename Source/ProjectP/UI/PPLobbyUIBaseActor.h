// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "PPLobbyUIBaseActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FSettingButtonDelegate);
DECLARE_MULTICAST_DELEGATE(FHelpButtonDelegate);
DECLARE_MULTICAST_DELEGATE(FExitButtonDelegate);

UCLASS()
class PROJECTP_API APPLobbyUIBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPLobbyUIBaseActor();

	FSettingButtonDelegate SettingButtonDelegate;
	
	UFUNCTION(BlueprintCallable)
	void ToggleSettingWidgetVisible();

	UFUNCTION(BlueprintCallable)
	void ToggleHelpWidgetVisible();
	
	UFUNCTION(BlueprintCallable)
	void ToggleExitCheckWidgetVisible();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> LobbyWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> SettingWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> HelpWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = WidgetCompnent)
	TObjectPtr<UWidgetComponent> ExitCheckWidgetComponent;
	
};
