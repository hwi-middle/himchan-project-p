// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPSettingUIWidget.h"
#include "Components/CheckBox.h"
#include "Components/PostProcessComponent.h"
#include "Components/Slider.h"
#include "Engine/PostProcessVolume.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPSaveSettingOption.h"
#include "Sound/SoundClass.h"

void UPPSettingUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(MasterSoundClass && BGMSoundClass && SFXSoundClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Get SoundClass Accepted"));
	}
	TArray<AActor*> PostProcessVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APostProcessVolume::StaticClass(), PostProcessVolumes);
	if(PostProcessVolumes.Num() > 0)
	{
		PostProcessVolume = Cast<APostProcessVolume>(PostProcessVolumes[0]);
		if(PostProcessVolume)
		{
			UE_LOG(LogTemp, Log, TEXT("Get World's PostProcessVolume Completed"));
		}
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->ConsoleCommand(TEXT(""));
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
	//CameraTurnValueLowButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ApplyCameraTurnValueLow);
	//CameraTurnValueMiddleButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ApplyCameraTurnValueMiddle);
	//CameraTurnValueHighButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ApplyCameraTurnValueHigh);
	
	ExitSettingUIButton->OnClicked.AddDynamic(this, &UPPSettingUIWidget::ExitSettingUI);
	
	LoadSettingData();
}

void UPPSettingUIWidget::SaveSettingData()
{
	TObjectPtr<UPPGameInstance> CurrentGI = Cast<UPPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	

	// 만약 게임 플레이 저장/불러오기 기능을 구현한다고 해도 설정은 여러개 저장 할 일이 없기 때문에 인덱스 0 고정
	// 파일 이름 또한 마찬가지로 생성자에서 설정한 초기 값 사용
	if(CurrentGI->SaveSettingOption)
	{
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
		MasterSoundVolumeSlider->SetValue(CurrentGI->SaveSettingOption->MasterSoundVolumeSliderValue);
		MasterSoundVolumeSlider->OnValueChanged.Broadcast(MasterSoundVolumeSlider->GetValue());
		
		BGMSoundVolumeSlider->SetValue(CurrentGI->SaveSettingOption->BGMSoundVolumeSliderValue);
		BGMSoundVolumeSlider->OnValueChanged.Broadcast(BGMSoundVolumeSlider->GetValue());
		
		SFXSoundVolumeSlider->SetValue(CurrentGI->SaveSettingOption->SFXSoundVolumeSliderValue);
		SFXSoundVolumeSlider->OnValueChanged.Broadcast(SFXSoundVolumeSlider->GetValue());
		
		MasterSoundToggle->SetIsChecked(CurrentGI->SaveSettingOption->bMasterSoundToggle);
		MasterSoundToggle->OnCheckStateChanged.Broadcast(MasterSoundToggle->IsChecked());
		
		BGMSoundToggle->SetIsChecked(CurrentGI->SaveSettingOption->bBGMSoundToggle);
		BGMSoundToggle->OnCheckStateChanged.Broadcast(BGMSoundToggle->IsChecked());
		
		SFXSoundToggle->SetIsChecked(CurrentGI->SaveSettingOption->bSFXSoundToggle);
		SFXSoundToggle->OnCheckStateChanged.Broadcast(SFXSoundToggle->IsChecked());
		
		DisplayBrightnessSlider->SetValue(CurrentGI->SaveSettingOption->DisplayBrightnessValue);
		DisplayBrightnessSlider->OnValueChanged.Broadcast(DisplayBrightnessSlider->GetValue());
		
		DisplayVignettingSlider->SetValue(CurrentGI->SaveSettingOption->DisplayVignettingValue);
		DisplayVignettingSlider->OnValueChanged.Broadcast(DisplayVignettingSlider->GetValue());
		
		PauseInterfaceDistanceSlider->SetValue(CurrentGI->SaveSettingOption->PauseInterfaceDistanceValue);
		PauseInterfaceDistanceSlider->OnValueChanged.Broadcast(PauseInterfaceDistanceSlider->GetValue());
		
		PauseInterfaceHeightSlider->SetValue(CurrentGI->SaveSettingOption->PauseInterfaceHeightValue);
		PauseInterfaceDistanceSlider->OnValueChanged.Broadcast(PauseInterfaceDistanceSlider->GetValue());
		
		LeftHandedSettingToggle->SetIsChecked(CurrentGI->SaveSettingOption->bUseLeftHandedSetting);
		LeftHandedSettingToggle->OnCheckStateChanged.Broadcast(LeftHandedSettingToggle->IsChecked());
		
		ControllerVibrationToggle->SetIsChecked(CurrentGI->SaveSettingOption->bUseControllerVibration);
		ControllerVibrationToggle->OnCheckStateChanged.Broadcast(ControllerVibrationToggle->IsChecked());
		
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
	SettingButtonDelegate.Broadcast(EWidgetType::Setting);
}

void UPPSettingUIWidget::ApplyMasterSoundToggle(bool IsChecked)
{
	if(IsChecked)
	{
		MasterSoundVolumeSlider->SetLocked(true);
		MasterSoundClass->Properties.Volume = 0;
	}
	else
	{
		MasterSoundVolumeSlider->SetLocked(false);
		MasterSoundClass->Properties.Volume = MasterSoundVolumeSlider->GetValue();
	}
}

void UPPSettingUIWidget::ApplyBGMSoundToggle(bool IsChecked)
{
	if(IsChecked)
	{
		BGMSoundVolumeSlider->SetLocked(true);
		BGMSoundClass->Properties.Volume = 0;
	}
	else
	{
		BGMSoundVolumeSlider->SetLocked(false);
		BGMSoundClass->Properties.Volume = BGMSoundVolumeSlider->GetValue();
	}
}

void UPPSettingUIWidget::ApplySFXSoundToggle(bool IsChecked)
{
	if(IsChecked)
	{
		SFXSoundVolumeSlider->SetLocked(true);
		SFXSoundClass->Properties.Volume = 0;
	}
	else
	{
		SFXSoundVolumeSlider->SetLocked(false);
		SFXSoundClass->Properties.Volume = SFXSoundVolumeSlider->GetValue();
	}
}

void UPPSettingUIWidget::ApplyPauseInterfaceDistanceSliderValue(float Value)
{
	// 일시정지 기능 구현 작업단계에서 할 예정
}

void UPPSettingUIWidget::ApplyPauseInterfaceHeightSliderValue(float Value)
{
	// 일시정지 기능 구현 작업단계에서 할 예정
}

