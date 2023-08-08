// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPSettingUIWidget.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Engine/PostProcessVolume.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPSaveSettingOption.h"
#include "Sound/SoundClass.h"

void UPPSettingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ExitSettingUIButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ExitSettingUI);
	LoadSettingData();
}

void UPPSettingUIWidget::SaveSettingData()
{
	TObjectPtr<UPPGameInstance> CurrentGI = Cast<UPPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// 만약 게임 플레이 내용 저장/불러오기 기능을 구현한다고 해도 설정은 여러개 저장 할 일이 없기 때문에 인덱스 0 고정
	// 파일 이름 또한 마찬가지로 생성자에서 설정한 초기 값 사용
	if(CurrentGI->SaveSettingOption)
	{
		// 서브위젯으로 세이브 전달
		UGameplayStatics::SaveGameToSlot(CurrentGI->SaveSettingOption, CurrentGI->SaveSettingOption->SaveFileName, 0);
		UE_LOG(LogTemp, Log, TEXT("Save SettingOption Data Completed"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Save SettingOption Data Completed"));
	}
}

void UPPSettingUIWidget::LoadSettingData()
{
	const TObjectPtr<UPPGameInstance> CurrentGI = Cast<UPPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(CurrentGI->SaveSettingOption)
	{
		// 서브위젯으로 세이브 전달
		UE_LOG(LogTemp, Log, TEXT("Load Setting Option SaveFile Completed"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Load Setting Option SaveFile Failed"));
	}
}

void UPPSettingUIWidget::ExitSettingUI()
{
	SaveSettingData();
}
