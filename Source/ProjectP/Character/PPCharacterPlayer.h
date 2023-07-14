// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPCharacterBase.h"
#include "EnhancedInputSubsystems.h"
#include "PPCharacterPlayer.generated.h"


UCLASS()
class PROJECTP_API APPCharacterPlayer : public APPCharacterBase
{
	GENERATED_BODY()
private:
	constexpr static float PLAYER_WALK_SPEED = 0.5f;
	constexpr static float PLAYER_RUN_SPEED = 1.0f;
	constexpr static float PLAYER_CAMERA_ROTATION = 90.0f;
	
public:
	APPCharacterPlayer();
	
	// Default Protected Section
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
	
	// Player Input And Movement Section
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetupCharacterControlData(const class UPPCharacterControlData* CharacterControlData) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPPCharacterControlData> PlayerControlData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PlayerMovementAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PlayerRunAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PlayerQuickRotationAction;
private:
	void PlayerMovement(const FInputActionValue& Value);
	void PlayerIsRunning(const FInputActionValue& Value);
	void PlayerQuickRotation(const FInputActionValue& Value);
	
	uint32 bIsRunning : 1;
	
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = PLAYER_WALK_SPEED;
	UPROPERTY(EditDefaultsOnly)
	float RunSpeed = PLAYER_RUN_SPEED;
	UPROPERTY(EditDefaultsOnly)
	float QuickRotationAngle = PLAYER_CAMERA_ROTATION;
};
