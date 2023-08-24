// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPGraphicSettingWidget.h"

void UPPGraphicSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	TextureQualityLowButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyTextureQualityLow);
	TextureQualityMiddleButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyTextureQualityMiddle);
	TextureQualityHighButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyTextureQualityHigh);
	
	ShadowQualityLowButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyShadowQualityLow);
	ShadowQualityMiddleButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyShadowQualityMiddle);
	ShadowQualityHighButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyShadowQualityHigh);

	EnableFXAAButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::SetCurrenAAToFXAA);
	EnableTAAButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::SetCurrenAAToTAA);
	
	AAQualityLowButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyAAQualityLow);
	AAQualityMiddleButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyAAQualityMiddle);
	AAQualityHighButton->OnClicked.AddDynamic(this, &UPPGraphicSettingWidget::ApplyAAQualityHigh);

	TQLowText->SetIsEnabled(false);
	TQMiddleText->SetIsEnabled(false);
	TQHighText->SetIsEnabled(false);
	SQLowText->SetIsEnabled(false);
	SQMiddleText->SetIsEnabled(false);
	SQHighText->SetIsEnabled(false);
	FXAAText->SetIsEnabled(false);
	TAAText->SetIsEnabled(false);
	AALowText->SetIsEnabled(false);
	AAMiddleText->SetIsEnabled(false);
	AAHighText->SetIsEnabled(false);
}

void UPPGraphicSettingWidget::SaveSettingData(UPPSaveSettingOption* SettingOption)
{
	const Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	SettingOption->TextureQualityValue = QualityLevels.TextureQuality;
	SettingOption->ShadowQualityValue = QualityLevels.ShadowQuality;
	SettingOption->AAQualityValue = QualityLevels.AntiAliasingQuality;
}


void UPPGraphicSettingWidget::LoadSettingData(UPPSaveSettingOption* SettingOption)
{
	switch (SettingOption->TextureQualityValue)
	{
	case EGraphicQuality::Low:
		TextureQualityLowButton->SetIsEnabled(false);
		TextureQualityLowButton->OnClicked.Broadcast();
		break;
	case EGraphicQuality::Middle:
		TextureQualityMiddleButton->SetIsEnabled(false);
		TextureQualityMiddleButton->OnClicked.Broadcast();
		break;
	case EGraphicQuality::High:
		TextureQualityHighButton->SetIsEnabled(false);
		TextureQualityHighButton->OnClicked.Broadcast();
		break;
	default:
		checkNoEntry();
	}

	switch (SettingOption->ShadowQualityValue)
	{
	case EGraphicQuality::Low:
		ShadowQualityLowButton->SetIsEnabled(false);
		ShadowQualityLowButton->OnClicked.Broadcast();
		break;
	case EGraphicQuality::Middle:
		ShadowQualityMiddleButton->SetIsEnabled(false);
		ShadowQualityMiddleButton->OnClicked.Broadcast();
		break;
	case EGraphicQuality::High:
		ShadowQualityHighButton->SetIsEnabled(false);
		ShadowQualityHighButton->OnClicked.Broadcast();
		break;
	default:
		checkNoEntry();
	}
	
	switch (SettingOption->AAType)
	{
	case EAAType::FXAA:
		EnableFXAAButton->SetIsEnabled(false);
		EnableFXAAButton->OnClicked.Broadcast();
		break;
	case EAAType::TAA:
		EnableTAAButton->SetIsEnabled(false);
		EnableTAAButton->OnClicked.Broadcast();
		break;
	default:
		checkNoEntry();
	}
	
	switch (SettingOption->AAQualityValue)
	{
	case EGraphicQuality::Low:
		AAQualityLowButton->SetIsEnabled(false);
		AAQualityLowButton->OnClicked.Broadcast();
		break;
	case EGraphicQuality::Middle:
		AAQualityMiddleButton->SetIsEnabled(false);
		AAQualityMiddleButton->OnClicked.Broadcast();
		break;
	case EGraphicQuality::High:
		AAQualityHighButton->SetIsEnabled(false);
		AAQualityHighButton->OnClicked.Broadcast();
		break;
	default:
		checkNoEntry();
	}
}

void UPPGraphicSettingWidget::ApplyTextureQualityLow()
{
	TextureQualityLowButton->SetIsEnabled(false);
	TextureQualityMiddleButton->SetIsEnabled(true);
	TextureQualityHighButton->SetIsEnabled(true);
	TQLowText->SetIsEnabled(true);
	TQMiddleText->SetIsEnabled(false);
	TQHighText->SetIsEnabled(false);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.TextureQuality = static_cast<int32>(EGraphicQuality::Low);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::ApplyTextureQualityMiddle()
{
	TextureQualityLowButton->SetIsEnabled(true);
	TextureQualityMiddleButton->SetIsEnabled(false);
	TextureQualityHighButton->SetIsEnabled(true);
	TQLowText->SetIsEnabled(false);
	TQMiddleText->SetIsEnabled(true);
	TQHighText->SetIsEnabled(false);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.TextureQuality = static_cast<int32>(EGraphicQuality::Middle);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::ApplyTextureQualityHigh()
{
	TextureQualityLowButton->SetIsEnabled(true);
	TextureQualityMiddleButton->SetIsEnabled(true);
	TextureQualityHighButton->SetIsEnabled(false);
	TQLowText->SetIsEnabled(false);
	TQMiddleText->SetIsEnabled(false);
	TQHighText->SetIsEnabled(true);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.TextureQuality = static_cast<int32>(EGraphicQuality::High);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::ApplyShadowQualityLow()
{
	ShadowQualityLowButton->SetIsEnabled(false);
	ShadowQualityMiddleButton->SetIsEnabled(true);
	ShadowQualityHighButton->SetIsEnabled(true);
	SQLowText->SetIsEnabled(true);
	SQMiddleText->SetIsEnabled(false);
	SQHighText->SetIsEnabled(false);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.ShadowQuality = static_cast<int32>(EGraphicQuality::Low);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::ApplyShadowQualityMiddle()
{
	ShadowQualityLowButton->SetIsEnabled(true);
	ShadowQualityMiddleButton->SetIsEnabled(false);
	ShadowQualityHighButton->SetIsEnabled(true);
	SQLowText->SetIsEnabled(false);
	SQMiddleText->SetIsEnabled(true);
	SQHighText->SetIsEnabled(false);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.ShadowQuality = static_cast<int32>(EGraphicQuality::Middle);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::ApplyShadowQualityHigh()
{
	ShadowQualityLowButton->SetIsEnabled(true);
	ShadowQualityMiddleButton->SetIsEnabled(true);
	ShadowQualityHighButton->SetIsEnabled(false);
	SQLowText->SetIsEnabled(false);
	SQMiddleText->SetIsEnabled(false);
	SQHighText->SetIsEnabled(true);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.ShadowQuality = static_cast<int32>(EGraphicQuality::High);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::SetCurrenAAToFXAA()
{
	FXAAText->SetIsEnabled(true);
	TAAText->SetIsEnabled(false);
	GEngine->Exec(GetWorld(), TEXT("r.DefaultFeature.AntiAliasing 1"));
	EnableFXAAButton->SetIsEnabled(false);
	EnableTAAButton->SetIsEnabled(true);
}

void UPPGraphicSettingWidget::SetCurrenAAToTAA()
{
	FXAAText->SetIsEnabled(false);
	TAAText->SetIsEnabled(true);
	GEngine->Exec(GetWorld(), TEXT("r.DefaultFeature.AntiAliasing 2"));
	EnableFXAAButton->SetIsEnabled(true);
	EnableTAAButton->SetIsEnabled(false);
}

void UPPGraphicSettingWidget::ApplyAAQualityLow()
{
	AAQualityLowButton->SetIsEnabled(false);
	AAQualityMiddleButton->SetIsEnabled(true);
	AAQualityHighButton->SetIsEnabled(true);
	AALowText->SetIsEnabled(true);
	AAMiddleText->SetIsEnabled(false);
	AAHighText->SetIsEnabled(false);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.AntiAliasingQuality = static_cast<int32>(EGraphicQuality::Low);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::ApplyAAQualityMiddle()
{
	AAQualityLowButton->SetIsEnabled(true);
	AAQualityMiddleButton->SetIsEnabled(false);
	AAQualityHighButton->SetIsEnabled(true);
	AALowText->SetIsEnabled(false);
	AAMiddleText->SetIsEnabled(true);
	AAHighText->SetIsEnabled(false);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.AntiAliasingQuality = static_cast<int32>(EGraphicQuality::Middle);
	SetQualityLevels(QualityLevels);
}

void UPPGraphicSettingWidget::ApplyAAQualityHigh()
{
	AAQualityLowButton->SetIsEnabled(true);
	AAQualityMiddleButton->SetIsEnabled(true);
	AAQualityHighButton->SetIsEnabled(false);
	AALowText->SetIsEnabled(false);
	AAMiddleText->SetIsEnabled(false);
	AAHighText->SetIsEnabled(true);
	Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
	QualityLevels.AntiAliasingQuality = static_cast<int32>(EGraphicQuality::High);
	SetQualityLevels(QualityLevels);
}
