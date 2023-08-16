// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundCue.h"
#include "PPSoundData.generated.h"

/**
 * 튜토리얼 가이드와 같은 트리거에 접근했을 때 호출되는 사운드는 인스턴스의 디테일 뷰에서 개별 지정
 */
UCLASS()
class PROJECTP_API UPPSoundData : public UDataAsset
{
	GENERATED_BODY()

	// Player
public:
	UPROPERTY(EditAnywhere, Category = "Player")
	TObjectPtr<USoundCue> PlayerHitSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player")
	TObjectPtr<USoundCue> PlayerWalkSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player")
	TObjectPtr<USoundCue> PlayerSprintSoundCue;

	// Gun
public:
	UPROPERTY(EditAnywhere, Category = "Gun")
	TObjectPtr<USoundCue> GunOnFireSoundCue;

	UPROPERTY(EditAnywhere, Category = "Gun")
	TObjectPtr<USoundCue> GunGrabOnHandSoundCue;

	UPROPERTY(EditAnywhere, Category = "Gun")
	TObjectPtr<USoundCue> GunCoolDownSoundCue;

	UPROPERTY(EditAnywhere, Category = "Gun")
	TObjectPtr<USoundCue> GunOverheatSoundCue;

	UPROPERTY(EditAnywhere, Category = "Gun")
	TObjectPtr<USoundCue> GunToggleFlashSoundCue;

	// Commander
public:
	UPROPERTY(EditAnywhere, Category = "Commander")
	TObjectPtr<USoundCue> CommanderHealthWaringSoundCue;

	UPROPERTY(EditAnywhere, Category = "Commander")
	TObjectPtr<USoundCue> CommanderVineGardenSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Commander")
	TObjectPtr<USoundCue> CommanderLeafTempestSoundCue;

	UPROPERTY(EditAnywhere, Category = "Commander")
	TObjectPtr<USoundCue> CommanderGreenFogSoundCue;

	UPROPERTY(EditAnywhere, Category = "Commander")
	TObjectPtr<USoundCue> CommanderThornWhipSoundCue;

	// Boss
public:
	UPROPERTY(EditAnywhere, Category = "Boss")
	TObjectPtr<USoundCue> BossVineGardenOmenSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss")
	TObjectPtr<USoundCue> BossLeafTempestOmenSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss")
	TObjectPtr<USoundCue> BossLeafTempestExplodeSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss")
	TObjectPtr<USoundCue> BossLeafTempestDestroySoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss")
	TObjectPtr<USoundCue> BossGreenFogOmenSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss")
	TObjectPtr<USoundCue> BossGreenFogSpawnSoundCue;

	// UI
public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TObjectPtr<USoundCue> WidgetMoveSoundCue;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TObjectPtr<USoundCue> WidgetOpenSoundCue;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TObjectPtr<USoundCue> WidgetCloseSoundCue;
};
