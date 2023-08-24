// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"
#include "Engine/PostProcessVolume.h"
#include "ProjectP/UI/Prologue/PPPrologueWidget.h"
#include "GameFramework/Actor.h"
#include "PPPrologueActor.generated.h"

UCLASS()
class PROJECTP_API APPPrologueActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPPrologueActor();
	void ClearAllTimerOnLevelChange();
	
protected:
	// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	void DisplayStringData();
	
	void LoadMainLevelSequence();
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> PrologueWidgetComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPPPrologueWidget> PrologueWidget;
	
	UPROPERTY()
	TObjectPtr<APostProcessVolume> PostProcessVolume;
		
	UPROPERTY()
	FTimerHandle StringDataChangeTimerHandle;

	UPROPERTY()
	FTimerHandle LoadMainLevelTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "PrologueWidget", DisplayName = "StringData")
	TArray<FDataTableRowHandle> PrologueStringDataHandle;

	UPROPERTY(EditAnywhere, Category = "PrologueWidget", DisplayName = "SubtitleChangeDelay")
	float HandleChangeTime;

	UPROPERTY(VisibleAnywhere)
	float NextArrayNum;
};
