// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPSettingUIWidget.h"

#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Util/PPSaveSettingOption.h"

void UPPSettingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MasterSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyMasterSliderValue);
	BGMSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyBGMSliderValue);
	SFXSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplySFXSliderValue);

	MasterSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyMasterSoundToggle);
	BGMSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyBGMSoundToggle);
	SFXSoundToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplySFXSoundToggle);

	DisplayBrightnessSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyDisplayBrightnessSliderValue);
	DisplayVignettingSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyDisplayVignettingSliderValue);

	PauseInterfaceDistanceSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyPauseInterfaceDistanceSliderValue);
	PauseInterfaceHeightSlider->OnValueChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyPauseInterfaceHeightSliderValue);

	LeftHandedSettingToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyLeftHandedSettingToggle);
	ControllerVibrationToggle->OnCheckStateChanged.AddDynamic(this, &UPPSettingUIWidget::ApplyControllerVibrationToggle);

	ExitSettingUIButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ExitSettingUI);
	LoadSettingData();
}

void UPPSettingUIWidget::SaveSettingData()
{
	TObjectPtr<UPPSaveSettingOption> SaveSettingInstance = Cast<UPPSaveSettingOption>(UGameplayStatics::CreateSaveGameObject(UPPSaveSettingOption::StaticClass()));

	SaveSettingInstance->MasterSoundVolumeSliderValue = MasterSoundVolumeSlider->GetValue();
	SaveSettingInstance->BGMSoundVolumeSliderValue = BGMSoundVolumeSlider->GetValue();
	SaveSettingInstance->SFXSoundVolumeSliderValue = SFXSoundVolumeSlider->GetValue();
	SaveSettingInstance->bMasterSoundToggle = MasterSoundToggle->IsChecked();
	SaveSettingInstance->bBGMSoundToggle = BGMSoundToggle->IsChecked();
	SaveSettingInstance->bSFXSoundToggle = SFXSoundToggle->IsChecked();
	
	SaveSettingInstance->DisplayBrightnessValue = DisplayBrightnessSlider->GetValue();
	SaveSettingInstance->DisplayVignettingValue = DisplayVignettingSlider->GetValue();
	
	SaveSettingInstance->PauseInterfaceDistanceValue = PauseInterfaceDistanceSlider->GetValue();
	SaveSettingInstance->PauseInterfaceHeightValue = PauseInterfaceHeightSlider->GetValue();
	SaveSettingInstance->bUseLeftHandedSetting = LeftHandedSettingToggle->IsChecked();
	SaveSettingInstance->bUseControllerVibration = ControllerVibrationToggle->IsChecked();

	// 만약 게임 플레이 저장/불러오기 기능을 구현한다고 해도 설정은 여러개 저장 할 일이 없기 때문에 인덱스 0 고정
	// 파일 이름 또한 마찬가지로 생성자에서 설정한 초기 값 사용
	UGameplayStatics::SaveGameToSlot(SaveSettingInstance, SaveSettingInstance->SaveFileName, 0);
	UE_LOG(LogTemp, Log, TEXT("Save SettingOption Data Completed"));
}

void UPPSettingUIWidget::LoadSettingData()
{
	TObjectPtr<UPPSaveSettingOption> SaveSettingInstance = Cast<UPPSaveSettingOption>(UGameplayStatics::CreateSaveGameObject(UPPSaveSettingOption::StaticClass()));
	SaveSettingInstance = Cast<UPPSaveSettingOption>(UGameplayStatics::LoadGameFromSlot(SaveSettingInstance->SaveFileName, 0));
	if(SaveSettingInstance)
	{
		MasterSoundVolumeSlider->SetValue(SaveSettingInstance->MasterSoundVolumeSliderValue);
		BGMSoundVolumeSlider->SetValue(SaveSettingInstance->BGMSoundVolumeSliderValue);
		SFXSoundVolumeSlider->SetValue(SaveSettingInstance->SFXSoundVolumeSliderValue);
		MasterSoundToggle->SetIsChecked(SaveSettingInstance->bMasterSoundToggle);
		BGMSoundToggle->SetIsChecked(SaveSettingInstance->bBGMSoundToggle);
		SFXSoundToggle->SetIsChecked(SaveSettingInstance->bSFXSoundToggle);

		DisplayBrightnessSlider->SetValue(SaveSettingInstance->DisplayBrightnessValue);
		DisplayVignettingSlider->SetValue(SaveSettingInstance->DisplayVignettingValue);

		PauseInterfaceDistanceSlider->SetValue(SaveSettingInstance->PauseInterfaceDistanceValue);
		PauseInterfaceHeightSlider->SetValue(SaveSettingInstance->PauseInterfaceHeightValue);
		LeftHandedSettingToggle->SetIsChecked(SaveSettingInstance->bUseLeftHandedSetting);
		ControllerVibrationToggle->SetIsChecked(SaveSettingInstance->bUseControllerVibration);

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
	SettingButtonDelegate.Broadcast();
}

void UPPSettingUIWidget::ApplyMasterSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyBGMSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplySFXSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyMasterSoundToggle(bool IsChecked)
{
	IsChecked ? MasterSoundVolumeSlider->SetLocked(true) : MasterSoundVolumeSlider->SetLocked(false);
}

void UPPSettingUIWidget::ApplyBGMSoundToggle(bool IsChecked)
{
	IsChecked ? BGMSoundVolumeSlider->SetLocked(true) : BGMSoundVolumeSlider->SetLocked(false);
}

void UPPSettingUIWidget::ApplySFXSoundToggle(bool IsChecked)
{
	IsChecked ? SFXSoundVolumeSlider->SetLocked(true) : SFXSoundVolumeSlider->SetLocked(false);
}

void UPPSettingUIWidget::ApplyDisplayBrightnessSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyDisplayVignettingSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyPauseInterfaceDistanceSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyPauseInterfaceHeightSliderValue(float Value)
{
	
}

void UPPSettingUIWidget::ApplyLeftHandedSettingToggle(bool IsChecked)
{
	//LeftHandedSettingDelegate.ExecuteIfBound(IsChecked);
}

void UPPSettingUIWidget::ApplyControllerVibrationToggle(bool IsChecked)
{
	//ControllerVibrationDelegate.ExecuteIfBound(IsChecked);
}
