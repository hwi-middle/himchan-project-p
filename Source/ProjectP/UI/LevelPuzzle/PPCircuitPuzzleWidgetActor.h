// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPCircuitPuzzleWidget.h"
#include "Components/BoxComponent.h"
#include "Components/Button.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectP/Object/PPEventCaller.h"
#include "PPCircuitPuzzleWidgetActor.generated.h"

UENUM()
enum class ECircuitDirection : uint8
{
	Top,
	Right,
	Bottom,
	Left
};

UCLASS()
class PROJECTP_API APPCircuitPuzzleWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPCircuitPuzzleWidgetActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetHalfWidthValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI")
	float WidgetWidthAddValue;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TObjectPtr<UWidgetComponent> CircuitPuzzleWidgetComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Widget")
	TObjectPtr<UPPCircuitPuzzleWidget> CircuitPuzzleWidget;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPPEventCaller> EventCallerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> TriggerBox;
	
private:
	void RotatePressedButton(UButton* Button, ECircuitNum ButtonNum);
	void RotateAction();
	void CheckCurrentButtonCorrect();
	ECircuitDirection SetNextDirection(ECircuitDirection Direction);

private:
	UPROPERTY()
	TObjectPtr<UButton> RotateButton;

	UPROPERTY()
	ECircuitNum RotateButtonNum; 
	
	UPROPERTY(EditAnywhere, DisplayName = "첫번째 회로 정답 방향")
	ECircuitDirection FirstCircuitTargetDirection;
	
	UPROPERTY(EditAnywhere, DisplayName = "두번째 회로 정답 방향")
	ECircuitDirection SecondCircuitTargetDirection;
	
	UPROPERTY(EditAnywhere, DisplayName = "세번째 회로 정답 방향")
	ECircuitDirection ThirdCircuitTargetDirection;

	UPROPERTY()
	ECircuitDirection CurrentFirstCircuitDirection;

	UPROPERTY()
	ECircuitDirection CurrentSecondCircuitDirection;

	UPROPERTY()
	ECircuitDirection CurrentThirdCircuitDirection;

	UPROPERTY()
	float StartRotation;
	
	UPROPERTY()
	float CurrentRotation;
	
	uint8 bIsFirstCircuitCorrected : 1;
	
	uint8 bIsSecondCircuitCorrected : 1;

	uint8 bIsThirdCircuitCorrected : 1;

	uint8 bIsRotationOnGoing : 1;

private:
	void DisplayWidgetBackgroundDelegate();
	void HideWidgetBackgroundDelegate();
	
private:
	FTimerHandle DisplayTimerHandle;

	FTimerHandle HideTimerHandle;
};
