// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/TestOnly/PPDebugWidget.h"

#include "Kismet/GameplayStatics.h"

void UPPDebugWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BossCharacter = CastChecked<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));
	PlayerCharacter = CastChecked<APPCharacterPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterPlayer::StaticClass()));
	Gun = CastChecked<APPGunBase>(UGameplayStatics::GetActorOfClass(GetWorld(), APPGunBase::StaticClass()));
	
}

void UPPDebugWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	BossCurrentHealth = BossCharacter->GetCurrentHealth();
	PlayerCurrentHealth = PlayerCharacter->GetCurrentHealth();
	GunCurrentOverheatGauge = Gun->GetCurrentOverheatGauge();
	GunAimingActorName = Gun->GetAimingActorName();

	FText LogText;
	DebugLogText->SetText(LogText);
}
