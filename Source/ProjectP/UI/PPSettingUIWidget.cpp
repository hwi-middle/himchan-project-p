// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPSettingUIWidget.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Game/PPGameInstance.h"
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
	TObjectPtr<UPPGameInstance> CurrentGI = Cast<UPPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	CurrentGI->SaveSettingOption->MasterSoundVolumeSliderValue = MasterSoundVolumeSlider->GetValue();
	CurrentGI->SaveSettingOption->BGMSoundVolumeSliderValue = BGMSoundVolumeSlider->GetValue();
	CurrentGI->SaveSettingOption->SFXSoundVolumeSliderValue = SFXSoundVolumeSlider->GetValue();
	CurrentGI->SaveSettingOption->bMasterSoundToggle = MasterSoundToggle->IsChecked();
	CurrentGI->SaveSettingOption->bBGMSoundToggle = BGMSoundToggle->IsChecked();
	CurrentGI->SaveSettingOption->bSFXSoundToggle = SFXSoundToggle->IsChecked();
	
	CurrentGI->SaveSettingOption->DisplayBrightnessValue = DisplayBrightnessSlider->GetValue();
	CurrentGI->SaveSettingOption->DisplayVignettingValue = DisplayVignettingSlider->GetValue();
	
	CurrentGI->SaveSettingOption->PauseInterfaceDistanceValue = PauseInterfaceDistanceSlider->GetValue();
	CurrentGI->SaveSettingOption->PauseInterfaceHeightValue = PauseInterfaceHeightSlider->GetValue();
	CurrentGI->SaveSettingOption->bUseLeftHandedSetting = LeftHandedSettingToggle->IsChecked();
	CurrentGI->SaveSettingOption->bUseControllerVibration = ControllerVibrationToggle->IsChecked();

	// 만약 게임 플레이 저장/불러오기 기능을 구현한다고 해도 설정은 여러개 저장 할 일이 없기 때문에 인덱스 0 고정
	// 파일 이름 또한 마찬가지로 생성자에서 설정한 초기 값 사용
	if(CurrentGI->SaveSettingOption != nullptr)
	{
		UGameplayStatics::SaveGameToSlot(CurrentGI->SaveSettingOption, CurrentGI->SaveSettingOption->SaveFileName, 0);
	}
	UE_LOG(LogTemp, Log, TEXT("Save SettingOption Data Completed"));
}

void UPPSettingUIWidget::LoadSettingData()
{
	TObjectPtr<UPPGameInstance> CurrentGI = Cast<UPPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(CurrentGI->SaveSettingOption)
	{
		MasterSoundVolumeSlider->SetValue(CurrentGI->SaveSettingOption->MasterSoundVolumeSliderValue);
		BGMSoundVolumeSlider->SetValue(CurrentGI->SaveSettingOption->BGMSoundVolumeSliderValue);
		SFXSoundVolumeSlider->SetValue(CurrentGI->SaveSettingOption->SFXSoundVolumeSliderValue);
		MasterSoundToggle->SetIsChecked(CurrentGI->SaveSettingOption->bMasterSoundToggle);
		BGMSoundToggle->SetIsChecked(CurrentGI->SaveSettingOption->bBGMSoundToggle);
		SFXSoundToggle->SetIsChecked(CurrentGI->SaveSettingOption->bSFXSoundToggle);

		DisplayBrightnessSlider->SetValue(CurrentGI->SaveSettingOption->DisplayBrightnessValue);
		DisplayVignettingSlider->SetValue(CurrentGI->SaveSettingOption->DisplayVignettingValue);

		PauseInterfaceDistanceSlider->SetValue(CurrentGI->SaveSettingOption->PauseInterfaceDistanceValue);
		PauseInterfaceHeightSlider->SetValue(CurrentGI->SaveSettingOption->PauseInterfaceHeightValue);
		LeftHandedSettingToggle->SetIsChecked(CurrentGI->SaveSettingOption->bUseLeftHandedSetting);
		ControllerVibrationToggle->SetIsChecked(CurrentGI->SaveSettingOption->bUseControllerVibration);

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
