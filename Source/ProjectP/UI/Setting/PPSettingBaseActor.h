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

	void OpenSubWidget(ESubWidgetType SubWidget);
	void ToggleSubWidgetPanel(const bool IsOpened, ESubWidgetType SwapSubWidget = ESubWidgetType::None);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UWidgetComponent> SettingWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UPPSettingUIWidget> SettingWidget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FTimerHandle SubWidgetControlTimer;
	/*
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FTimerHandle SubWidgetContentOpacityTimer;
	*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float WidgetAnimationTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float WidgetHeightAddValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float WidgetHalfHeightValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	uint32 bSubWidgetOpened : 1;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float WidgetAddOpacityValue;
	*/
};
