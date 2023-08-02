// Fill out your copyright notice in the Description page of Project Settings.


#include "PPVRHandAnimInstance.h"
#include "Math/UnrealMathUtility.h"

void UPPVRHandAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CurrentPoseAlphaThumbUp = FMath::FInterpTo(CurrentPoseAlphaThumbUp, PoseAlphaThumbUp, DeltaSeconds, 13.0f);
	CurrentPoseAlphaPoint = FMath::FInterpTo(CurrentPoseAlphaPoint, PoseAlphaPoint, DeltaSeconds, 13.0f);
}
