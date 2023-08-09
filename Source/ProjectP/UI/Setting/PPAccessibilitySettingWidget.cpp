// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPAccessibilitySettingWidget.h"

void UPPAccessibilitySettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LeftHandedSettingButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyLeftHandedSetting);
	RightHandedSettingButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyRightHandedSetting);
	ControllerVibrationToggle->OnCheckStateChanged.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyControllerVibrationToggle);
	// VRPawn 관련 작업 끝난 뒤 적용 예정
	CameraTurnValueLowButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueLow);
	CameraTurnValueMiddleButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueMiddle);
	CameraTurnValueHighButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueHigh);

	bUseLeftHandedSetting = false;
	/*
	 * Delegate에 VRPawn 함수 바인딩
	 */
}

void UPPAccessibilitySettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	SettingOption->bUseLeftHandedSetting = bUseLeftHandedSetting;
	SettingOption->bUseControllerVibration = ControllerVibrationToggle->IsChecked();
	SettingOption->CameraTurnValue = NewCameraTurnValue;
}

void UPPAccessibilitySettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	SettingOption->bUseLeftHandedSetting == true ? ApplyLeftHandedSetting() : ApplyRightHandedSetting();
	
	if(SettingOption->bUseControllerVibration)
	{
		ControllerVibrationToggle->SetIsChecked(true);
		ControllerVibrationToggle->OnCheckStateChanged.Broadcast(true);
	}
	
	NewCameraTurnValue = SettingOption->CameraTurnValue;
	switch (static_cast<uint8>(NewCameraTurnValue))
	{
	case ECameraTurnValue::Low:
		ApplyCameraTurnValueLow();
		break;
	case ECameraTurnValue::Middle:
		ApplyCameraTurnValueMiddle();
		break;
	case ECameraTurnValue::High:
		ApplyCameraTurnValueHigh();
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

void UPPAccessibilitySettingWidget::ApplyLeftHandedSetting()
{
	LeftHandedSettingButton->SetIsEnabled(false);
	RightHandedSettingButton->SetIsEnabled(true);
	
	LeftHandedOptionDelegate.Broadcast(true);
}

void UPPAccessibilitySettingWidget::ApplyRightHandedSetting()
{
	LeftHandedSettingButton->SetIsEnabled(true);
	RightHandedSettingButton->SetIsEnabled(false);
	
	LeftHandedOptionDelegate.Broadcast(false);
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueLow()
{
	CameraTurnValueLowButton->SetIsEnabled(false);
	CameraTurnValueMiddleButton->SetIsEnabled(true);
	CameraTurnValueHighButton->SetIsEnabled(true);
	
	CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Low));
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueMiddle()
{
	CameraTurnValueLowButton->SetIsEnabled(true);
	CameraTurnValueMiddleButton->SetIsEnabled(false);
	CameraTurnValueHighButton->SetIsEnabled(true);
	
	CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Middle));
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueHigh()
{
	CameraTurnValueLowButton->SetIsEnabled(true);
	CameraTurnValueMiddleButton->SetIsEnabled(true);
	CameraTurnValueHighButton->SetIsEnabled(false);
	
	CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::High));
}
