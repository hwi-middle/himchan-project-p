// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Tutorial/PPTriggerWidgetBase.h"

#include "ProjectP/Character/PPCharacterPlayer.h"

// Sets default values
APPTriggerWidgetBase::APPTriggerWidgetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GuideWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	RootComponent = TriggerBox;
	GuideWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APPTriggerWidgetBase::BeginPlay()
{
	Super::BeginPlay();
	//GuideWidget = CastChecked<UUserWidget>(GuideWidgetComponent->GetUserWidgetObject());
	//GuideWidget->SetRenderOpacity(0.0f);
}

// Called every frame
void APPTriggerWidgetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPTriggerWidgetBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	TObjectPtr<APPCharacterPlayer> Player = Cast<APPCharacterPlayer>(OtherActor);
	if(Player)
	{
		
	}
}

void APPTriggerWidgetBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	TObjectPtr<APPCharacterPlayer> Player = Cast<APPCharacterPlayer>(OtherActor);
	if(Player)
	{
		
	}
}

