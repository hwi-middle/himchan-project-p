// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/TestOnly/PPBossHealthBarWidget.h"

#include "Kismet/GameplayStatics.h"

void UPPBossHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BossCharacter = CastChecked<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));
	MaxHealth = BossCharacter->GetCurrentHealth();
	CurrentHealth = MaxHealth;
}

void UPPBossHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	CurrentHealth = BossCharacter->GetCurrentHealth();
	float HealthBarPercent = CurrentHealth / MaxHealth;
	HealthBar->SetPercent(HealthBarPercent);
	
	UE_LOG(LogTemp, Log, TEXT("CurrentHealth : %f"), CurrentHealth);
}
