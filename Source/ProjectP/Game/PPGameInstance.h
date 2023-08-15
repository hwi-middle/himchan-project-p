// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/ObjectLibrary.h"
#include "ProjectP/Util/StringDataTable.h"
#include "ProjectP/Util/PPSaveSettingOption.h"
#include "PPGameInstance.generated.h"

/**
 * 인스턴스 = 싱글톤 객체와 유사한 역할(메모리를 지속적으로 차지함)
 * 가급적이면 전역적으로 관리해야 하는 내용만을 포함시키도록 한다.
 */
UCLASS()
class PROJECTP_API UPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPPGameInstance();

public:
	
	FStringDataTable* GetStringDataTable(const FName RowName);

	TObjectPtr<USoundCue> GetSoundCue(const FString SoundName);

	FORCEINLINE TObjectPtr<UPPSaveSettingOption> GetSaveSettingOption() const { return SaveSettingOption; }
	
private:
    // 인스턴스내에 환경설정 값을 저장시켜놓고 레벨을 옮길 때 레벨에서 인스턴스의 환경설정 값을 적용
	UPROPERTY()
	TObjectPtr<UPPSaveSettingOption> SaveSettingOption;

	// 튜토리얼, 자막 등에 사용 할 문자열 데이터 테이블
	UPROPERTY()
	TObjectPtr<UDataTable> StringDataTable;

	// 사운드 재생 및 등록에 사용 할 사운드맵
	UPROPERTY()
	TMap<FString, USoundCue*> SoundCueMap;
};

