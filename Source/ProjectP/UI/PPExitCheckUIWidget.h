// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPExitCheckUIWidget.generated.h"

/**
 * 로비 이동 or 게임 종료 관리
 * 최초 구현 단계에선 게임플레이 단계에선 로비로, 로비에선 프로그램 종료로 이어지게끔 함
 * 논의에 따라 게임플레이 단계에서 즉시 프로그램을 종료 가능하게 할 경우 
 */
UCLASS(meta =(DisableNativeTick))
class PROJECTP_API UPPExitCheckUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	virtual void NativeConstruct() override;
};
