// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPasswordPuzzleWidgetActor.h"

#include "PPPasswordPuzzleWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
APPPasswordPuzzleWidgetActor::APPPasswordPuzzleWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PasswordPuzzleWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PasswordPuzzleUIWidget"));
	PasswordPuzzleWidgetComponent->SetupAttachment(RootComponent);
	PasswordPuzzleWidgetComponent->SetCastShadow(false);

	EventCallerComponent = CreateDefaultSubobject<UPPEventCaller>(TEXT("Event Caller"));
}

// Called when the game starts or when spawned
void APPPasswordPuzzleWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	PasswordPuzzleWidget = CastChecked<UPPPasswordPuzzleWidget>(PasswordPuzzleWidgetComponent->GetUserWidgetObject());
	PasswordPuzzleWidget->SetCorrectPassword(CorrectPassword);
	PasswordPuzzleWidget->CorrectPasswordDelegate.AddUObject(this, &APPPasswordPuzzleWidgetActor::DeliverCorrectEvent);
}

// Called every frame
void APPPasswordPuzzleWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

