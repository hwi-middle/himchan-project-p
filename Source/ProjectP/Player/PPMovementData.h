// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPMovementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPMovementData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="VR Move")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category="VR Move")
	float SprintSpeed;
	
	UPROPERTY(EditAnywhere, Category="VR Move")
	float SnapTurnDegrees;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> SprintAction;
};
