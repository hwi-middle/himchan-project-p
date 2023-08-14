// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StringDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FStringDataTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName Kor;
};

UCLASS()
class PROJECTP_API UPPStringDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
