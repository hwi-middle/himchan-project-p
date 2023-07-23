// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PPVRPawn.generated.h"

UCLASS()
class PROJECTP_API APPVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true), Category = "MotionTracking")
	TObjectPtr<class UMotionControllerComponent> LeftMotionController;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true), Category = "MotionTracking")
	TObjectPtr<class UMotionControllerComponent> RightMotionController;

private:
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true), Category = "Input")
	TObjectPtr<class UPPMovementData> MovementData;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<class USceneComponent> VROrigin;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<class UFloatingPawnMovement> FloatingPawnMovement;

private:
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> TurnAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> SprintAction;
	
	UPROPERTY()
	float SnapTurnDegrees;

	UPROPERTY()
	float MoveSpeed;
	
private:
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void EnableSprint(const FInputActionValue& Value);
	void DisableSprint(const FInputActionValue& Value);
};
