// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Tutorial/PPTriggerWidgetBase.h"
#include "GameFramework/Character.h"

// Sets default values
APPTriggerWidgetBase::APPTriggerWidgetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TutorialWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	RootComponent = TriggerBox;
	TutorialWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APPTriggerWidgetBase::BeginPlay()
{
	Super::BeginPlay();
	TutorialWidget = CastChecked<UPPTutorialUIWidget>(TutorialWidgetComponent->GetUserWidgetObject());
	TutorialWidget->SetPanelOpacity(0.0f);
}

// Called every frame
void APPTriggerWidgetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPTriggerWidgetBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	TObjectPtr<ACharacter> Player = Cast<ACharacter>(OtherActor);
	if(Player)
	{
		if(GetWorldTimerManager().IsTimerActive(WidgetAnimationTimer))
		{
			GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
		}
		// 위젯 애니메이션 연출
		GetWorldTimerManager().SetTimer(WidgetAnimationTimer, FTimerDelegate::CreateLambda([&]()
		{
			TutorialWidget->SetPanelOpacity(TutorialWidget->GetPanelOpacity() + WidgetOpacityAddValue);
			UE_LOG(LogTemp, Log, TEXT("Current Opacity = %f"), TutorialWidget->GetPanelOpacity());
			if(TutorialWidget->GetPanelOpacity() >= 1.0f)
			{
				TutorialWidget->SetPanelOpacity(1.0f);
				GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
			}
		}), WidgetAnimationTick, true);
	}
}

void APPTriggerWidgetBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	TObjectPtr<ACharacter> Player = Cast<ACharacter>(OtherActor);
	if(Player)
	{
		if(GetWorldTimerManager().IsTimerActive(WidgetAnimationTimer))
		{
			GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
		}
		// 위젯 애니메이션 연출
		GetWorldTimerManager().SetTimer(WidgetAnimationTimer, FTimerDelegate::CreateLambda([&]()
		{
			TutorialWidget->SetPanelOpacity(TutorialWidget->GetPanelOpacity() - WidgetOpacityAddValue);
			if(TutorialWidget->GetPanelOpacity() <= 0.0f)
			{
				TutorialWidget->SetPanelOpacity(0.0f);
				GetWorldTimerManager().ClearTimer(WidgetAnimationTimer);
			}
		}), WidgetAnimationTick, true);
	}
}

