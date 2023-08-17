// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Prop/Weapon/PPGunBase.h"
#include "PPDebugWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPDebugWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> DebugLogText;
	
private:
	UPROPERTY()
	TObjectPtr<class APPCharacterBoss> BossCharacter;

	UPROPERTY()
	TObjectPtr<class APPCharacterPlayer> PlayerCharacter;
	
	UPROPERTY()
	TObjectPtr<class APPGunBase> Gun;
	
	UPROPERTY()
	float BossCurrentHealth;
	
	UPROPERTY()
	float PlayerCurrentHealth;

	UPROPERTY()
	float GunCurrentOverheatGauge;

	UPROPERTY()
	FString GunAimingActorName;
	
};
