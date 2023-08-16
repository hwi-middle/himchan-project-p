// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Tutorial/PPTriggerWidgetBase.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Game/PPGameInstance.h"

// Sets default values
APPTriggerWidgetBase::APPTriggerWidgetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TutorialWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(400.0f, 400.0f, 400.0f));
	TriggerBox->SetupAttachment(RootComponent);
	TutorialWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APPTriggerWidgetBase::BeginPlay()
{
	Super::BeginPlay();
	
	TutorialWidget = CastChecked<UPPTutorialUIWidget>(TutorialWidgetComponent->GetUserWidgetObject());
	//TutorialWidget->SetBackgroundOpacity(0.0f);
	TutorialWidget->SetPadding(FMargin(WidgetHalfWidthValue, TutorialWidget->GetPadding().Top, WidgetHalfWidthValue, TutorialWidget->GetPadding().Bottom));
	TutorialWidget->SetGuidePanelOpacity(0.0f);
	
	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	TriggerEnterSoundCue = GameInstance->GetSoundData()->WidgetOpenSoundCue;
	TriggerOutSoundCue = GameInstance->GetSoundData()->WidgetCloseSoundCue;
	bIsFirstTriggered = true;
}

// Called every frame
void APPTriggerWidgetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPTriggerWidgetBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	TObjectPtr<ACharacter> Player = Cast<ACharacter>(OtherActor);
	if(Player)
	{
		OverlapActor = OtherActor;
		if(bIsFirstTriggered)
		{
			UGameplayStatics::PlaySound2D(this, CommanderSoundCue);
			bIsFirstTriggered = false;
		}
		UGameplayStatics::PlaySound2D(this, TriggerEnterSoundCue);
		
		// 애니메이션 도중 이벤트 발생시 기존 애니메이션 중지
		if(GetWorldTimerManager().IsTimerActive(BackgroundOpacityTimer) || GetWorldTimerManager().IsTimerActive(GuidePanelOpacityTimer))
		{
			GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
			GetWorldTimerManager().ClearTimer(GuidePanelOpacityTimer);
		}
		
		// 위젯 애니메이션. 배경 표시 후 내용 표시
		GetWorldTimerManager().SetTimer(BackgroundOpacityTimer, FTimerDelegate::CreateLambda([&]()
		{
			TutorialWidget->AddWidgetWidthValue(-WidgetWidthAddValue);
			if(TutorialWidget->GetPadding().Left <= 0.0f)
			{
				TutorialWidget->AddWidgetWidthValue(0.0f);
				GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
				DisplayWidgetContents();
			}
		}), WidgetAnimationTick, true);
		
		// 위젯이 활성화 된 상태에서는 플레이어를 바라보도록 함
		GetWorldTimerManager().SetTimer(TurnToPlayerTimer, FTimerDelegate::CreateLambda([&]()
		{
			FVector LookVector = -OverlapActor->GetActorForwardVector();
			TutorialWidgetComponent->SetRelativeRotation(LookVector.Rotation());
		}), WidgetRotateDelay, true);
	}
}

void APPTriggerWidgetBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	GetWorldTimerManager().ClearTimer(TurnToPlayerTimer);
	TObjectPtr<ACharacter> Player = Cast<ACharacter>(OtherActor);
	if(Player)
	{
		UGameplayStatics::PlaySound2D(this, TriggerOutSoundCue);
		
		// 애니메이션 도중 이벤트 발생시 기존 애니메이션 중지
		if(GetWorldTimerManager().IsTimerActive(BackgroundOpacityTimer) || GetWorldTimerManager().IsTimerActive(GuidePanelOpacityTimer))
		{
			GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
			GetWorldTimerManager().ClearTimer(GuidePanelOpacityTimer);
		}
		// 위젯 애니메이션. 내용 숨긴 후 배경 숨기기
		GetWorldTimerManager().SetTimer(GuidePanelOpacityTimer, FTimerDelegate::CreateLambda([&]()
		{
			TutorialWidget->SetGuidePanelOpacity(TutorialWidget->GetGuidePanelOpacity() - WidgetOpacityAddValue);
			if(TutorialWidget->GetGuidePanelOpacity() <= 0.0f)
			{
				TutorialWidget->SetGuidePanelOpacity(0.0f);
				GetWorldTimerManager().ClearTimer(GuidePanelOpacityTimer);
				HideWidgetBackground();
			}
		}), WidgetAnimationTick, true);
	}
}

void APPTriggerWidgetBase::DisplayWidgetContents()
{
	GetWorldTimerManager().SetTimer(GuidePanelOpacityTimer, FTimerDelegate::CreateLambda([&]()
	{
		TutorialWidget->SetGuidePanelOpacity(TutorialWidget->GetGuidePanelOpacity() + WidgetOpacityAddValue);
		if(TutorialWidget->GetGuidePanelOpacity() >= 1.0f)
		{
			TutorialWidget->SetGuidePanelOpacity(1.0f);
			GetWorldTimerManager().ClearTimer(GuidePanelOpacityTimer);
		}
	}), WidgetAnimationTick, true);
}

void APPTriggerWidgetBase::HideWidgetBackground()
{
	GetWorldTimerManager().SetTimer(BackgroundOpacityTimer, FTimerDelegate::CreateLambda([&]()
	{
		TutorialWidget->AddWidgetWidthValue(WidgetWidthAddValue);
		if(TutorialWidget->GetPadding().Left >= WidgetHalfWidthValue)
		{
			TutorialWidget->AddWidgetWidthValue(WidgetHalfWidthValue);
			GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
		}
	}), WidgetAnimationTick, true);
}

