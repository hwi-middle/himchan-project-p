// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPAccessibilitySettingWidget.h"
#include "ProjectP/Player/PPVRPawn.h"
void UPPAccessibilitySettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LeftHandedSettingButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyLeftHandedSetting);
	RightHandedSettingButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyRightHandedSetting);

	CameraTurnValueLowButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueLow);
	CameraTurnValueMiddleButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueMiddle);
	CameraTurnValueHighButton->OnClicked.AddDynamic(this, &UPPAccessibilitySettingWidget::ApplyCameraTurnValueHigh);

	IsRightHandMainly = false;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		APPVRPawn* VRPawn = Cast<APPVRPawn>(PlayerController->GetPawn());
		RightHandMainlyDelegate.AddUObject(VRPawn, &APPVRPawn::SetRightHandMainly);
		CameraTurnValueSettingDelegate.AddUObject(VRPawn, &APPVRPawn::SetTurnDegrees);
		VibrationOptionDelegate.AddUObject(PlayerController, &APlayerController::SetDisableHaptics);
	}
	CTVLowText->SetIsEnabled(false);
	CTVMiddleText->SetIsEnabled(false);
	CTVHighText->SetIsEnabled(false);
	LeftHandText->SetIsEnabled(false);
	RightHandText->SetIsEnabled(false);
}

void UPPAccessibilitySettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	SettingOption->bIsRightHandMainly = IsRightHandMainly;
	SettingOption->CameraTurnValue = NewCameraTurnValue;
}

void UPPAccessibilitySettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	SettingOption->bIsRightHandMainly == true ? ApplyRightHandedSetting() : ApplyLeftHandedSetting();
	
	NewCameraTurnValue = SettingOption->CameraTurnValue;
	switch (static_cast<uint32>(NewCameraTurnValue))
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

void UPPAccessibilitySettingWidget::ApplyLeftHandedSetting()
{
	LeftHandedSettingButton->SetIsEnabled(false);
	RightHandedSettingButton->SetIsEnabled(true);
	LeftHandText->SetIsEnabled(true);
	RightHandText->SetIsEnabled(false);
	IsRightHandMainly = false;
	RightHandMainlyDelegate.Broadcast(false);
}

void UPPAccessibilitySettingWidget::ApplyRightHandedSetting()
{
	LeftHandedSettingButton->SetIsEnabled(true);
	RightHandedSettingButton->SetIsEnabled(false);
	LeftHandText->SetIsEnabled(false);
	RightHandText->SetIsEnabled(true);
	IsRightHandMainly = true;
	RightHandMainlyDelegate.Broadcast(true);
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueLow()
{
	CameraTurnValueLowButton->SetIsEnabled(false);
	CameraTurnValueMiddleButton->SetIsEnabled(true);
	CameraTurnValueHighButton->SetIsEnabled(true);
	CTVLowText->SetIsEnabled(true);
	CTVMiddleText->SetIsEnabled(false);
	CTVHighText->SetIsEnabled(false);
	NewCameraTurnValue = static_cast<float>(ECameraTurnValue::Low);
	
	CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Low));
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueMiddle()
{
	CameraTurnValueLowButton->SetIsEnabled(true);
	CameraTurnValueMiddleButton->SetIsEnabled(false);
	CameraTurnValueHighButton->SetIsEnabled(true);
	CTVLowText->SetIsEnabled(false);
	CTVMiddleText->SetIsEnabled(true);
	CTVHighText->SetIsEnabled(false);
	NewCameraTurnValue = static_cast<float>(ECameraTurnValue::Middle);
	
	CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::Middle));
}

void UPPAccessibilitySettingWidget::ApplyCameraTurnValueHigh()
{
	CameraTurnValueLowButton->SetIsEnabled(true);
	CameraTurnValueMiddleButton->SetIsEnabled(true);
	CameraTurnValueHighButton->SetIsEnabled(false);
	CTVLowText->SetIsEnabled(false);
	CTVMiddleText->SetIsEnabled(false);
	CTVHighText->SetIsEnabled(true);
	NewCameraTurnValue = static_cast<float>(ECameraTurnValue::High);
	
	CameraTurnValueSettingDelegate.Broadcast(static_cast<float>(ECameraTurnValue::High));
}
