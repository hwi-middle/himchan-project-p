// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPVitalWidget.h"

#include "ProjectP/Character/PPCharacterPlayer.h"

void UPPVitalWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerCharacter = Cast<APPCharacterPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterPlayer::StaticClass()));
	if(PlayerCharacter)
	{
		PlayerMaximumHealth = PlayerCharacter->GetCurrentHealth();
	}
	
	ImageMaximumScale = 1.3f;
	ImageMinimumScale = 1.0f;
	ImageScalingValue = FVector2D(0.005f, 0.005f);
	bIsUpScaling = true;
}

void UPPVitalWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(PlayerCharacter)
	{
		PlayerCurrentHealth = PlayerCharacter->GetCurrentHealth();
		VitalRadialSlider->SetValue(PlayerCurrentHealth);
		float VitalPercentage = PlayerCurrentHealth / PlayerMaximumHealth;
		float SliderColorGreen = 1.0f * VitalPercentage;
		float SliderColorRed;
		if(PlayerCurrentHealth < PlayerMaximumHealth / 2)
		{
			SliderColorRed = 1.5f - 1.0f * VitalPercentage;
		}
		else
		{
			SliderColorRed = 1.0f - 1.0f * VitalPercentage;
		}
		FLinearColor SliderColor = FVector3f(SliderColorRed, SliderColorGreen, 0.0f);
		VitalRadialSlider->SetSliderProgressColor(SliderColor);
	}
	
	if(bIsUpScaling)
	{
		FWidgetTransform WidgetTransform = VitalImage->GetRenderTransform();
		WidgetTransform.Scale += ImageScalingValue;
		VitalImage->SetRenderTransform(WidgetTransform);
		if(WidgetTransform.Scale.X >= ImageMaximumScale)
		{
			bIsUpScaling = false;
		}
	}
	else
	{
		FWidgetTransform WidgetTransform = VitalImage->GetRenderTransform();
		WidgetTransform.Scale -= ImageScalingValue;
		VitalImage->SetRenderTransform(WidgetTransform);
		if(WidgetTransform.Scale.X <= ImageMinimumScale)
		{
			bIsUpScaling = true;
		}
	}
}
