// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/TestOnly/PPDebugWidget.h"
#include "Kismet/GameplayStatics.h"

void UPPDebugWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BossCharacter = Cast<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));
	PlayerCharacter = Cast<APPCharacterPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterPlayer::StaticClass()));
	Gun = Cast<APPGunBase>(UGameplayStatics::GetActorOfClass(GetWorld(), APPGunBase::StaticClass()));
}

void UPPDebugWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FString LogString;
	if(BossCharacter)
	{
		BossCurrentHealth = BossCharacter->GetCurrentHealth();
		FString BossHealthText = FString::Printf(TEXT("보스 현재 체력 : %.2f \n"), BossCurrentHealth);
		LogString.Append(BossHealthText);
	}
	
	if(PlayerCharacter)
	{
		PlayerCurrentHealth = PlayerCharacter->GetCurrentHealth();
		FString PlayerHealthText = FString::Printf(TEXT("플레이어 현재 체력 : %.2f \n"), PlayerCurrentHealth);
		LogString.Append(PlayerHealthText);
	}
	
	if(Gun)
	{
		GunCurrentOverheatGauge = Gun->GetCurrentOverheatGauge();
		FString GunOverheatGaugeText = FString::Printf(TEXT("총기 현재 과열게이지 : %.2f \n"), GunCurrentOverheatGauge);
		
		GunAimingActorName = Gun->GetAimingActorName();
		FString GunAimingActorText = FString::Printf(TEXT("총기 현재 조준대상 : %s \n"), *GunAimingActorName);

		GunUnavailableTimeRemains = Gun->GetUnavailableTimeRemains();
		FString GunUnavailableTimeRemainsText = FString::Printf(TEXT("총기 조작불능 시간 : %.2f Second \n"), GunUnavailableTimeRemains);
		
		LogString.Append(GunOverheatGaugeText);
		LogString.Append(GunAimingActorText);
		LogString.Append(GunUnavailableTimeRemainsText);
	}
	
	const FText LogText = FText::FromString(LogString);
	DebugLogText->SetText(LogText);
}
