// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Pause/PPPauseWidget.h"

void UPPPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UPPPauseWidget::ResumeGame);
	SettingButton->OnClicked.AddDynamic(this, &UPPPauseWidget::ActivateSettingWidget);
	ExitButton->OnClicked.AddDynamic(this, &UPPPauseWidget::ActivateExitWidget);
}
