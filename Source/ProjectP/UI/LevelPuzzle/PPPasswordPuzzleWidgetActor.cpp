// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPasswordPuzzleWidgetActor.h"

#include "PPPasswordPuzzleWidget.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "ProjectP/Player/PPVRPawn.h"

// Sets default values
APPPasswordPuzzleWidgetActor::APPPasswordPuzzleWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PasswordPuzzleWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PasswordPuzzleUIWidget"));
	PasswordPuzzleWidgetComponent->SetupAttachment(RootComponent);
	PasswordPuzzleWidgetComponent->SetCastShadow(false);
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	EventCallerComponent = CreateDefaultSubobject<UPPEventCaller>(TEXT("Event Caller"));
}

// Called when the game starts or when spawned
void APPPasswordPuzzleWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	PasswordPuzzleWidget = CastChecked<UPPPasswordPuzzleWidget>(PasswordPuzzleWidgetComponent->GetUserWidgetObject());
	PasswordPuzzleWidget->SetCorrectPassword(CorrectPassword);
	PasswordPuzzleWidget->SetWidgetWidthValue(WidgetHalfWidthValue);
	PasswordPuzzleWidget->CorrectPasswordDelegate.AddUObject(this, &APPPasswordPuzzleWidgetActor::DeliverCorrectEvent);
	
}

// Called every frame
void APPPasswordPuzzleWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPPasswordPuzzleWidgetActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	TObjectPtr<APPVRPawn> Player = Cast<APPVRPawn>(OtherActor);
	TObjectPtr<ACharacter> TestPlayer = Cast<ACharacter>(OtherActor);
	if(Player || TestPlayer)
	{
		// 애니메이션 도중 이벤트 발생시 기존 애니메이션 중지
		if(GetWorldTimerManager().IsTimerActive(DisplayTimerHandle) || GetWorldTimerManager().IsTimerActive(HideTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(DisplayTimerHandle);
			GetWorldTimerManager().ClearTimer(HideTimerHandle);
		}
		
		// 위젯 애니메이션. 배경 표시 후 내용 표시
		GetWorldTimerManager().SetTimer(DisplayTimerHandle, this, &APPPasswordPuzzleWidgetActor::DisplayWidgetBackgroundDelegate, 0.01f, true);
	}
}

void APPPasswordPuzzleWidgetActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	TObjectPtr<APPVRPawn> Player = Cast<APPVRPawn>(OtherActor);
	TObjectPtr<ACharacter> TestPlayer = Cast<ACharacter>(OtherActor);
	if(Player || TestPlayer)
	{
		// 애니메이션 도중 이벤트 발생시 기존 애니메이션 중지
		if(GetWorldTimerManager().IsTimerActive(DisplayTimerHandle) || GetWorldTimerManager().IsTimerActive(HideTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(DisplayTimerHandle);
			GetWorldTimerManager().ClearTimer(HideTimerHandle);
		}
		
		// 위젯 애니메이션. 내용 숨긴 후 배경 숨기기
		GetWorldTimerManager().SetTimer(HideTimerHandle, this, &APPPasswordPuzzleWidgetActor::HideWidgetBackgroundDelegate, 0.01f, true);
	}
}

void APPPasswordPuzzleWidgetActor::DisplayWidgetBackgroundDelegate()
{
	PasswordPuzzleWidget->AddWidgetWidthValue(-WidgetWidthAddValue);
	if (PasswordPuzzleWidget->GetWidgetWidthValue() <= 0.0f)
	{
		PasswordPuzzleWidget->SetWidgetWidthValue(0.f);
		GetWorldTimerManager().ClearTimer(DisplayTimerHandle);
	}
}

void APPPasswordPuzzleWidgetActor::HideWidgetBackgroundDelegate()
{
	PasswordPuzzleWidget->AddWidgetWidthValue(WidgetWidthAddValue);
	if (PasswordPuzzleWidget->GetWidgetWidthValue() >= WidgetHalfWidthValue)
	{
		PasswordPuzzleWidget->SetWidgetWidthValue(WidgetHalfWidthValue);
		GetWorldTimerManager().ClearTimer(HideTimerHandle);
	}
}
