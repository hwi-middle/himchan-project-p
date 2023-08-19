// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Sound/SoundCue.h"
#include "ProjectP/Util/PPSoundData.h"
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

private:
	void ClearAllTimerOnLevelChange();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE void SetTurnDegrees(const float Degrees) { SnapTurnDegrees = Degrees; }
private:
	void InitVROrigin();
	void InitVRHands();

private:
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true), Category = "Hand")
	TObjectPtr<class APPVRHand> LeftHand;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true), Category = "Hand")
	TObjectPtr<class APPVRHand> RightHand;

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
	UPROPERTY(VisibleAnywhere)
	TArray<USoundCue*> WalkSoundCueArray;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USoundCue> WalkSoundCue;
	
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
	TObjectPtr<class UInputAction> GrabLeftAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> GrabRightAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> IndexCurlLeftAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> IndexCurlRightAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> PointLeftAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> PointRightAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> ThumbUpLeftAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> ThumbUpRightAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> LeftXButtonPressAction;

	UPROPERTY()
	TObjectPtr<class UInputAction> RightBButtonPressAction;

	UPROPERTY()
	FTimerHandle MoveSoundTimerHandle;

	UPROPERTY()
	float WalkSoundRate;

	UPROPERTY()
	float SprintSoundRate;
	
	UPROPERTY()
	float SnapTurnDegrees;

	UPROPERTY()
	float MoveSpeed;
	
	UPROPERTY()
	float WidgetInteractionDistance;

private:
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void GrabLeft(const FInputActionValue& Value);
	void GrabRight(const FInputActionValue& Value);
	void IndexCurlLeft(const FInputActionValue& Value);
	void IndexCurlRight(const FInputActionValue& Value);
	void PointLeft(const FInputActionValue& Value);
	void PointRight(const FInputActionValue& Value);
	void ThumbUpLeft(const FInputActionValue& Value);
	void ThumbUpRight(const FInputActionValue& Value);
	void StartMove(const FInputActionValue& Value);
	void CompleteMove(const FInputActionValue& Value);
	void ToggleSprint(const FInputActionValue& Value);
	void ToggleFlash(const FInputActionValue& Value);
	
private:
	void CancelOrCompleteGrabLeft();
	void CancelOrCompleteGrabRight();
	void CancelOrCompleteIndexCurlLeft();
	void CancelOrCompleteIndexCurlRight();
	void CompletePointLeft();
	void CompletePointRight();
	void CompleteThumbUpLeft();
	void CompleteThumbUpRight();
private:
	void ToggleWidgetInteraction(const FInputActionValue& Value);
};
