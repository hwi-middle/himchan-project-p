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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	uint32 bIsIdle : 1;

public:
	FORCEINLINE void SetCloseAlpha(const float Value) { CloseAlpha = Value; }
	FORCEINLINE void SetIsIdle(const bool Value) { bIsIdle = Value; }
};
