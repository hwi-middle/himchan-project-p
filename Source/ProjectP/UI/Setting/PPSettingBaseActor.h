// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPSettingUIWidget.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "ProjectP/Enumeration/PPSubWidgetType.h"
#include "PPSettingBaseActor.generated.h"

UCLASS()
class PROJECTP_API APPSettingBaseActor : public AActor
{
	GENERATED_BODY()

public:
	APPSettingBaseActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> SettingWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UPPSettingUIWidget> SettingWidget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FTimerHandle SubWidgetControlTimer;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FTimerHandle SubWidgetContentOpacityTimer;
};
