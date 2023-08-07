// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Setting/PPGraphicSettingWidget.h"

void UPPGraphicSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	TextureQualityLowButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyTextureQualityLow);
	TextureQualityMiddleButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyTextureQualityMiddle);
	TextureQualityHighButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyTextureQualityHigh);
	
	ShadowQualityLowButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyShadowQualityLow);
	ShadowQualityMiddleButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyShadowQualityMiddle);
	ShadowQualityHighButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyShadowQualityHigh);

	EnableFXAAButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::SetCurrenAAToFXAA);
	AAQualityLowButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyAAQualityLow);
	AAQualityLowButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyAAQualityMiddle);
	AAQualityLowButton->OnCheckStateChanged.AddDynamic(this, &UPPGraphicSettingWidget::ApplyAAQualityHigh);
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
		TextureQualityLowButton->SetIsChecked(true);
		TextureQualityLowButton->OnCheckStateChanged.Broadcast(true);
		break;
	case EGraphicQuality::Middle:
		TextureQualityMiddleButton->SetIsChecked(true);
		TextureQualityMiddleButton->OnCheckStateChanged.Broadcast(true);
		break;
	case EGraphicQuality::High:
		TextureQualityHighButton->SetIsChecked(true);
		TextureQualityHighButton->OnCheckStateChanged.Broadcast(true);
		break;
	default:
		checkNoEntry();
	}

	switch (SettingOption->ShadowQualityValue)
	{
	case EGraphicQuality::Low:
		ShadowQualityLowButton->SetIsChecked(true);
		ShadowQualityLowButton->OnCheckStateChanged.Broadcast(true);
		break;
	case EGraphicQuality::Middle:
		ShadowQualityMiddleButton->SetIsChecked(true);
		ShadowQualityMiddleButton->OnCheckStateChanged.Broadcast(true);
		break;
	case EGraphicQuality::High:
		ShadowQualityHighButton->SetIsChecked(true);
		ShadowQualityHighButton->OnCheckStateChanged.Broadcast(true);
		break;
	default:
		checkNoEntry();
	}
	
	switch (SettingOption->AAType)
	{
	case EAAType::FXAA:
		EnableFXAAButton->SetIsChecked(true);
		EnableFXAAButton->OnCheckStateChanged.Broadcast(true);
		break;
	case EAAType::TAA:
		EnableTAAButton->SetIsChecked(true);
		EnableTAAButton->OnCheckStateChanged.Broadcast(true);
		break;
	default:
		checkNoEntry();
	}
	
	switch (SettingOption->AAQualityValue)
	{
	case EGraphicQuality::Low:
		AAQualityLowButton->SetIsChecked(true);
		AAQualityLowButton->OnCheckStateChanged.Broadcast(true);
		break;
	case EGraphicQuality::Middle:
		AAQualityMiddleButton->SetIsChecked(true);
		AAQualityMiddleButton->OnCheckStateChanged.Broadcast(true);
		break;
	case EGraphicQuality::High:
		AAQualityHighButton->SetIsChecked(true);
		AAQualityHighButton->OnCheckStateChanged.Broadcast(true);
		break;
	default:
		checkNoEntry();
	}
}

void UPPGraphicSettingWidget::ApplyTextureQualityLow(bool IsChecked)
{
	if(IsChecked)
	{
		TextureQualityMiddleButton->SetIsChecked(false);
		TextureQualityHighButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.TextureQuality = static_cast<int32>(EGraphicQuality::Low);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::ApplyTextureQualityMiddle(bool IsChecked)
{
	if(IsChecked)
	{
		TextureQualityLowButton->SetIsChecked(false);
		TextureQualityHighButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.TextureQuality = static_cast<int32>(EGraphicQuality::Middle);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::ApplyTextureQualityHigh(bool IsChecked)
{
	if(IsChecked)
	{
		TextureQualityLowButton->SetIsChecked(false);
		TextureQualityMiddleButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.TextureQuality = static_cast<int32>(EGraphicQuality::High);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::ApplyShadowQualityLow(bool IsChecked)
{
	if(IsChecked)
	{
		ShadowQualityMiddleButton->SetIsChecked(false);
		ShadowQualityHighButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.ShadowQuality = static_cast<int32>(EGraphicQuality::Low);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::ApplyShadowQualityMiddle(bool IsChecked)
{
	if(IsChecked)
	{
		ShadowQualityLowButton->SetIsChecked(false);
		ShadowQualityHighButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.ShadowQuality = static_cast<int32>(EGraphicQuality::Middle);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::ApplyShadowQualityHigh(bool IsChecked)
{
	if(IsChecked)
	{
		ShadowQualityLowButton->SetIsChecked(false);
		ShadowQualityMiddleButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.ShadowQuality = static_cast<int32>(EGraphicQuality::High);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::SetCurrenAAToFXAA(bool IsChecked)
{
	if(IsChecked)
	{
		GEngine->Exec(GetWorld(), TEXT("r.DefaultFeature.AntiAliasing 1"));
		EnableTAAButton->SetIsChecked(false);
	}
}

void UPPGraphicSettingWidget::SetCurrenAAToTAA(bool IsChecked)
{
	if(IsChecked)
	{
		GEngine->Exec(GetWorld(), TEXT("r.DefaultFeature.AntiAliasing 2"));
		EnableFXAAButton->SetIsChecked(false);
	}
}

void UPPGraphicSettingWidget::ApplyAAQualityLow(bool IsChecked)
{
	if(IsChecked)
	{
		AAQualityMiddleButton->SetIsChecked(false);
		AAQualityHighButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.AntiAliasingQuality = static_cast<int32>(EGraphicQuality::Low);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::ApplyAAQualityMiddle(bool IsChecked)
{
	if(IsChecked)
	{
		AAQualityLowButton->SetIsChecked(false);
		AAQualityHighButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.AntiAliasingQuality = static_cast<int32>(EGraphicQuality::Middle);
		SetQualityLevels(QualityLevels);
	}
}

void UPPGraphicSettingWidget::ApplyAAQualityHigh(bool IsChecked)
{
	if(IsChecked)
	{
		AAQualityLowButton->SetIsChecked(false);
		AAQualityMiddleButton->SetIsChecked(false);
		Scalability::FQualityLevels QualityLevels = Scalability::GetQualityLevels();
		QualityLevels.AntiAliasingQuality = static_cast<int32>(EGraphicQuality::High);
		SetQualityLevels(QualityLevels);
	}
}
