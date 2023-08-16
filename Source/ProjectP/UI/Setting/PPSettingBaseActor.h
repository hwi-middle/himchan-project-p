// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "ProjectP/UI/Setting/PPSettingUIWidget.h"
#include "ProjectP/Enumeration/PPSubWidgetType.h"
#include "PPSettingBaseActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FMainWidgetDelegate)

UCLASS()
class PROJECTP_API APPSettingBaseActor : public AActor
{
	GENERATED_BODY()

public:
	APPSettingBaseActor();

	
	FMainWidgetDelegate MainWidgetDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ExitButtonBroadcast();
	
	void OpenSubWidget(ESubWidgetType SubWidget = ESubWidgetType::None);
	void CloseSubWidgetPanel();
	void OpenSubWidgetPanel();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UWidgetComponent> SettingWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UPPSettingUIWidget> SettingWidget;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FTimerHandle SubWidgetCloseTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FTimerHandle SubWidgetOpenTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundCue> WidgetOpenSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundCue> WidgetCloseSoundCue;
	
	/*
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FTimerHandle SubWidgetContentOpacityTimer;
	*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float WidgetAnimationTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float WidgetHeightOffsetAddValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float SubWidgetHalfHeightValue;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	uint32 bSubWidgetOpened : 1;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	uint32 bIsFirstClick : 1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UI")
	ESubWidgetType SwapSubWidget;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float WidgetAddOpacityValue;
	*/
};
