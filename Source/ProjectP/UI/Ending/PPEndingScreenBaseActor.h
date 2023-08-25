// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ProjectP/UI/Ending/PPEndingUIWidget.h"
#include "PPEndingScreenBaseActor.generated.h"

UCLASS()
class PROJECTP_API APPEndingScreenBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPEndingScreenBaseActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ClearAllTimerOnLevelChange();

protected:
	void FadeInOrOutScreenImage(const bool IsFaded);

	// 람다안의람다안의람다안의람다식으로 합치기 가능
	void ActivateCreditPanel();
	void MoveCreditPanel();
	void ExitToLobby();
	
	void EnableAutoFadeTimer();
	void ToggleLight(bool IsEnable);

	// Variable Section
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetCompoent")
	TObjectPtr<UWidgetComponent> EndingScreenWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetCompoent")
	TObjectPtr<UPPEndingUIWidget> EndingUIWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetCompoent")
	TObjectPtr<USpotLightComponent> ScreenLight;

	UPROPERTY(EditAnywhere, Category = "PrologueWidget", DisplayName = "StringData")
	TArray<FDataTableRowHandle> PrologueStringDataHandle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float AutoFadeTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float ImageFadeSequenceTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float MaxCreditBottomPosition;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float CreditAddPositionValue;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float LightMaxIntensity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float LightEnhanceIntensityPerTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float ExitToLobbyDelay;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ending Options")
	float TimerTick;

	UPROPERTY(VisibleAnywhere)
	float NextArrayNum;
	
	// 동시에 돌아가는 타이머가 없다시피 해서 묶어버릴까 고민중
	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle FadeSequenceTimer;

	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle CreditMoveTimer;
	
	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle DelayTimer;

	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle LightIntensityControlTimer;
	
};
