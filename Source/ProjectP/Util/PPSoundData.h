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

	// BGM
public:
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "로비 배경음악")
	TObjectPtr<USoundCue> LobbyBGMSoundCue;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "튜토리얼 배경음악")
	TObjectPtr<USoundCue> TutorialBGMSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "보스전 배경음악")
	TObjectPtr<USoundCue> BossBGMSoundCue;

	UPROPERTY(EditAnywhere, Category = "BGM", DisplayName = "엔딩 배경음악")
	TObjectPtr<USoundCue> EndingBGMSoundCue;
	
	// Player
public:
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 피격음")
	TObjectPtr<USoundCue> PlayerHitSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어가 일정 체력 이하일 때 효과음")
	TObjectPtr<USoundCue> PlayerLowHealthSoundCue;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어가 사망할 때 효과음")
	TObjectPtr<USoundCue> PlayerDeadSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 발소리 리스트")
	TArray<USoundCue*> PlayerWalkTypeASoundCueArray;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 걷기 발소리 간격")
	float WalkSoundRate;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "플레이어 달리기 발소리 간격")
	float SprintSoundRate;
	
	// Gun
public:
	UPROPERTY(EditAnywhere, Category = "Gun", DisplayName = "총기 발사음 리스트")
	TArray<USoundCue*> GunOnFireSoundCueArray;

	UPROPERTY(EditAnywhere, Category = "Gun", DisplayName = "총기 줍는 소리")
	TObjectPtr<USoundCue> GunGrabOnHandSoundCue;

	UPROPERTY(EditAnywhere, Category = "Gun", DisplayName = "총기 냉각음")
	TObjectPtr<USoundCue> GunCoolDownSoundCue;

	UPROPERTY(EditAnywhere, Category = "Gun", DisplayName = "총기 과열게이지 상승음")
	TObjectPtr<USoundCue> IncreaseGunOverheatGaugeSoundCue;

	UPROPERTY(EditAnywhere, Category = "Gun", DisplayName = "총기 최대과열 효과음")
	TObjectPtr<USoundCue> GunOverheatGaugeMaxSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Gun", DisplayName = "총기 플래시 라이트 토글 효과음")
	TObjectPtr<USoundCue> GunToggleFlashSoundCue;

	// Commander
public:
	UPROPERTY(EditAnywhere, Category = "Commander", DisplayName = "커맨더 플레이어 체력 경고음")
	TObjectPtr<USoundCue> CommanderHealthWaringSoundCue;

	UPROPERTY(EditAnywhere, Category = "Commander", DisplayName = "커맨더 덩굴정원 경고음")
	TArray<USoundCue*> CommanderVGWaringSoundCueArray;
	
	UPROPERTY(EditAnywhere, Category = "Commander", DisplayName = "커맨더 리프템페스트 경고음")
	TArray<USoundCue*> CommanderLTWaringSoundCueArray;

	UPROPERTY(EditAnywhere, Category = "Commander", DisplayName = "커맨더 녹빛안개 경고음")
	TArray<USoundCue*> CommanderGFWaringSoundCueArray;
	
	// Boss
public:
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 덩굴정원 전조음")
	TObjectPtr<USoundCue> BossVGOmenSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 리프템페스트 전조음")
	TObjectPtr<USoundCue> BossLTOmenSoundCue;
	
	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 리프템페스트 폭발음")
	TObjectPtr<USoundCue> BossLTExplodeSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 리프템페스트 파괴음")
	TArray<USoundCue*> BossLTDestroySoundCueArray;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 녹빛안개 경고음")
	TObjectPtr<USoundCue> BossGFOmenSoundCue;

	UPROPERTY(EditAnywhere, Category = "Boss", DisplayName = "보스 녹빛안개 생성음")
	TObjectPtr<USoundCue> BossGFSpawnSoundCue;

	// UI
public:
	UPROPERTY(EditAnywhere, Category = "Widget", DisplayName = "UI 이동음")
	TObjectPtr<USoundCue> WidgetMoveSoundCue;

	UPROPERTY(EditAnywhere, Category = "Widget", DisplayName = "UI 열기 사운드")
	TObjectPtr<USoundCue> WidgetOpenSoundCue;

	UPROPERTY(EditAnywhere, Category = "Widget", DisplayName = "UI 닫기 사운드")
	TObjectPtr<USoundCue> WidgetCloseSoundCue;
};
