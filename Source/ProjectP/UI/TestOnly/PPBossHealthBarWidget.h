// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "PPBossHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPBossHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
private:
	UPROPERTY()
	TObjectPtr<class APPCharacterBoss> BossCharacter;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY()
	float CurrentHealth;
	
};
