// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "Components/Button.h"
#include "PPPatternTestWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPPatternTestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void StartLeafTempestPattern() {  }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void StartGreenFogPattern() {  }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void StartGardenPattern() {  }
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI", meta =(BindWidget))
	TObjectPtr<UButton> LeafButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI", meta =(BindWidget))
	TObjectPtr<UButton> GardenButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="UI", meta =(BindWidget))
	TObjectPtr<UButton> FogButton;

	UPROPERTY(EditAnywhere)
	int LeafTempestNum;

	UPROPERTY(EditAnywhere)
	int VineGardenNum;
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<APPCharacterBoss> BossCharacter;
};
