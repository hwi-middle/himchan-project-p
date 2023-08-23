// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PPTentacleAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPTentacleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint32 bShow : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint32 bHide : 1;

public:
	FORCEINLINE void Show() { bShow = true; }
	FORCEINLINE void Hide() { bHide = true; }
};
