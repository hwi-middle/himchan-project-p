// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PPVRHandAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPVRHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint32 bMirror : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float PoseAlphaGrasp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float PoseAlphaIndexCurl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float PoseAlphaPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float PoseAlphaThumbUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float CurrentPoseAlphaThumbUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float CurrentPoseAlphaPoint;

public:
	FORCEINLINE void SetIsMirror(const uint32 Value) { bMirror = Value; }
	FORCEINLINE void SetPoseAlphaGrasp(const float Value) { PoseAlphaGrasp = Value; }
	FORCEINLINE void SetPoseAlphaIndexCurl(const float Value) { PoseAlphaIndexCurl = Value; }
	FORCEINLINE void SetPoseAlphaThumbUp(const float Value) { PoseAlphaThumbUp = Value; }
	FORCEINLINE void SetPoseAlphaPoint(const float Value) { PoseAlphaPoint = Value; }
};
