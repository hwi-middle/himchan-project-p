// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPAccessibilitySettingWidget.h"

void UPPAccessibilitySettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LeftHandedSettingButton->OnCheckStateChanged.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyLeftHandedSetting);
	RightHandedSettingButton->OnCheckStateChanged.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyRightHandedSetting);
	ControllerVibrationToggle->OnCheckStateChanged.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyControllerVibrationToggle);
	// VRPawn 관련 작업 끝난 뒤 적용 예정
	CameraTurnValueLowButton->OnCheckStateChanged.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueLow);
	CameraTurnValueMiddleButton->OnCheckStateChanged.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueMiddle);
	CameraTurnValueHighButton->OnCheckStateChanged.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueHigh);

	/*
	 * Delegate에 VRPawn 함수 바인딩
	 */
}

void UPPAccessibilitySettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	SettingOption->bUseLeftHandedSetting = LeftHandedSettingButton->IsChecked();
	SettingOption->bUseControllerVibration = ControllerVibrationToggle->IsChecked();
	SettingOption->CameraTurnValue = NewCameraTurnValue;
}

void UPPAccessibilitySettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	if(SettingOption->bUseLeftHandedSetting)
	{
		LeftHandedSettingButton->SetIsChecked(true);
		LeftHandedSettingButton->OnCheckStateChanged.Broadcast(true);
	}
	else
	{
		RightHandedSettingButton->SetIsChecked(true);
		RightHandedSettingButton->OnCheckStateChanged.Broadcast(true);
	}
	
	if(SettingOption->bUseControllerVibration)
	{
		ControllerVibrationToggle->SetIsChecked(true);
		ControllerVibrationToggle->OnCheckStateChanged.Broadcast(true);
	}
	
	NewCameraTurnValue = SettingOption->CameraTurnValue;
	switch (static_cast<uint8>(NewCameraTurnValue))
	{
	case ECameraTurnValue::Low:
		CameraTurnValueLowButton->SetIsChecked(true);
		CameraTurnValueLowButton->OnCheckStateChanged.Broadcast(true);
		break;
	case ECameraTurnValue::Middle:
		CameraTurnValueLowButton->SetIsChecked(true);
		CameraTurnValueMiddleButton->OnCheckStateChanged.Broadcast(true);
		break;
	case ECameraTurnValue::High:
		CameraTurnValueHighButton->SetIsChecked(true);
		CameraTurnValueHighButton->OnCheckStateChanged.Broadcast(true);
		break;
	default:
		checkNoEntry();
	}
}

void UPPAccessibilitySettingWidget::ApplyPauseInterfaceDistanceSliderValue(float Value)
{
	// 일시정지 기능 구현 작업단계에서 할 예정
}

void UPPAccessibilitySettingWidget::ApplyPauseInterfaceHeightSliderValue(float Value)
{
	// 일시정지 기능 구현 작업단계에서 할 예정
}

void UPPAccessibilitySettingWidget::ApplyLeftHandedSetting(const bool IsChecked)
{
	if(IsChecked)
	{
		RightHandedSettingButton->SetIsChecked(false);
		LeftHandedOptionDelegate.Broadcast(true);
	}
}

void UPPAccessibilitySettingWidget::ApplyRightHandedSetting(const bool IsChecked)
{
	if(IsChecked)
	{
		LeftHandedSettingButton->SetIsChecked(false);
		LeftHandedOptionDelegate.Broadcast(false);
	}
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueLow(const bool IsChecked)
{
	if(IsChecked)
	{
		CameraTurnValueMiddleButton->SetIsChecked(false);
		CameraTurnValueHighButton->SetIsChecked(false);
		CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Low));
	}
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueMiddle(const bool IsChecked)
{
	if(IsChecked)
	{
		CameraTurnValueLowButton->SetIsChecked(false);
		CameraTurnValueHighButton->SetIsChecked(false);
		CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Middle));
	}
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueHigh(const bool IsChecked)
{
	if(IsChecked)
	{
		CameraTurnValueLowButton->SetIsChecked(false);
		CameraTurnValueMiddleButton->SetIsChecked(false);
		CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::High));
	}
}
