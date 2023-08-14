// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/PPPatternTestWidget.h"

#include "Kismet/GameplayStatics.h"

void UPPPatternTestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	LeafButton->OnClicked.AddDynamic(this, &UPPPatternTestWidget::StartLeafTempestPattern);
	GardenButton->OnClicked.AddDynamic(this, &UPPPatternTestWidget::StartGardenPattern);
	FogButton->OnClicked.AddDynamic(this, &UPPPatternTestWidget::StartGreenFogPattern);
	
	BossCharacter = CastChecked<APPCharacterBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APPCharacterBoss::StaticClass()));
}
