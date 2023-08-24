// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PPBossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float CloseAlpha;

public:
	FORCEINLINE void SetCloseAlpha(const float Value) { CloseAlpha = Value; }
};
