// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Tutorial/PPTriggerWidgetBase.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Player/PPVRPawn.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPTriggerWidgetBase::APPTriggerWidgetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TutorialWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetBoxExtent(FVector(400.0f, 400.0f, 400.0f));
	RootComponent = TriggerBox;
	TutorialWidgetComponent->SetupAttachment(RootComponent);

	TutorialWidgetClass = FPPConstructorHelper::FindAndGetClass<UUserWidget>(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Project-P/UI/Blueprints/Tutorial/TutorialWidget.TutorialWidget_C'"));
	TitleStringDataHandle.DataTable = FPPConstructorHelper::FindAndGetObject<UDataTable>(TEXT("/Script/Engine.DataTable'/Game/Project-P/DataTable/StringData.StringData'"), EAssertionLevel::Check);
	InfoStringDataHandle.DataTable = FPPConstructorHelper::FindAndGetObject<UDataTable>(TEXT("/Script/Engine.DataTable'/Game/Project-P/DataTable/StringData.StringData'"), EAssertionLevel::Check);
}

// Called when the game starts or when spawned
void APPTriggerWidgetBase::BeginPlay()
{
	Super::BeginPlay();

	TutorialWidgetComponent->SetWidgetClass(TutorialWidgetClass);
	TutorialWidget = Cast<UPPTutorialUIWidget>(TutorialWidgetComponent->GetUserWidgetObject());
	TutorialWidget->SetPadding(FMargin(WidgetHalfWidthValue, TutorialWidget->GetPadding().Top, WidgetHalfWidthValue, TutorialWidget->GetPadding().Bottom));
	TutorialWidget->SetTutorialPanelOpacity(0.0f);
	
	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPTriggerWidgetBase::ClearAllTimerOnLevelChange);

	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	TriggerEnterSoundCue = SoundData->WidgetOpenSoundCue;
	TriggerOutSoundCue = SoundData->WidgetCloseSoundCue;

	TutorialWidget->SetTutorialImage(TutorialImage);
	const FStringDataTable* TitleString = TitleStringDataHandle.GetRow<FStringDataTable>(TitleStringDataHandle.RowName.ToString());
	if(TitleString)
	{
		TutorialWidget->SetTitleText(TitleString->Kor.ToString());
	}
	const FStringDataTable* InfoString = InfoStringDataHandle.GetRow<FStringDataTable>(InfoStringDataHandle.RowName.ToString());
	if(InfoString)
	{
		TutorialWidget->SetInfoText(InfoString->Kor.ToString());
	}
	
}

void APPTriggerWidgetBase::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
	GetWorldTimerManager().ClearTimer(TutorialPanelOpacityTimer);
	GetWorldTimerManager().ClearTimer(TurnToPlayerTimer);
	BackgroundOpacityTimer.Invalidate();
	TutorialPanelOpacityTimer.Invalidate();
	TurnToPlayerTimer.Invalidate();
}

// Called every frame
void APPTriggerWidgetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPTriggerWidgetBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	TObjectPtr<APPVRPawn> Player = Cast<APPVRPawn>(OtherActor);
	TObjectPtr<ACharacter> TestPlayer = Cast<ACharacter>(OtherActor);
	if(Player || TestPlayer)
	{
		LoadDelegate.Broadcast();
		OverlapActor = OtherActor;
		switch (CommanderSoundTriggerType)
		{
		case EEventTriggerType::None:
			break;
		case  EEventTriggerType::OneTimeOnly:
			UGameplayStatics::PlaySound2D(this, CommanderSoundCue);
			CommanderSoundTriggerType = EEventTriggerType::None;
			break;
		case EEventTriggerType::AnyTime:
			UGameplayStatics::PlaySound2D(this, CommanderSoundCue);
			break;
		default:
			checkNoEntry();
		}
		UGameplayStatics::PlaySound2D(this, TriggerEnterSoundCue);
		
		// 애니메이션 도중 이벤트 발생시 기존 애니메이션 중지
		if(GetWorldTimerManager().IsTimerActive(BackgroundOpacityTimer) || GetWorldTimerManager().IsTimerActive(TutorialPanelOpacityTimer))
		{
			GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
			GetWorldTimerManager().ClearTimer(TutorialPanelOpacityTimer);
		}
		
		// 위젯 애니메이션. 배경 표시 후 내용 표시
		GetWorldTimerManager().SetTimer(BackgroundOpacityTimer, this, APPTriggerWidgetBase::DisplayWidgetBackgroundDelegate, WidgetAnimationTick, true);
		
		// 위젯이 활성화 된 상태에서는 플레이어를 바라보도록 함
		GetWorldTimerManager().SetTimer(TurnToPlayerTimer, this, APPTriggerWidgetBase::WidgetFocusOnPlayerDelegate, WidgetRotateDelay, true);
	}
}

void APPTriggerWidgetBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	GetWorldTimerManager().ClearTimer(TurnToPlayerTimer);
	
	TObjectPtr<APPVRPawn> Player = Cast<APPVRPawn>(OtherActor);
	TObjectPtr<ACharacter> TestPlayer = Cast<ACharacter>(OtherActor);
	if(Player || TestPlayer)
	{
		UGameplayStatics::PlaySound2D(this, TriggerOutSoundCue);
		
		// 애니메이션 도중 이벤트 발생시 기존 애니메이션 중지
		if(GetWorldTimerManager().IsTimerActive(BackgroundOpacityTimer) || GetWorldTimerManager().IsTimerActive(TutorialPanelOpacityTimer))
		{
			GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
			GetWorldTimerManager().ClearTimer(TutorialPanelOpacityTimer);
		}
		// 위젯 애니메이션. 내용 숨긴 후 배경 숨기기
		GetWorldTimerManager().SetTimer(TutorialPanelOpacityTimer, this, APPTriggerWidgetBase::HideWidgetContentsDelegate, WidgetAnimationTick, true);
	}
}

void APPTriggerWidgetBase::DisplayWidgetContents()
{
	GetWorldTimerManager().SetTimer(TutorialPanelOpacityTimer, this, APPTriggerWidgetBase::DisplayWidgetContentsDelegate, WidgetAnimationTick, true);
}

void APPTriggerWidgetBase::HideWidgetBackground()
{
	GetWorldTimerManager().SetTimer(BackgroundOpacityTimer, this, APPTriggerWidgetBase::HideWidgetBackgroundDelegate, WidgetAnimationTick, true);
}

void APPTriggerWidgetBase::DisplayWidgetBackgroundDelegate()
{
	TutorialWidget->AddWidgetWidthValue(-WidgetWidthAddValue);
	if (TutorialWidget->GetPadding().Left <= 0.0f)
	{
		TutorialWidget->AddWidgetWidthValue(0.0f);
		GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
		DisplayWidgetContents();
	}
}

void APPTriggerWidgetBase::HideWidgetBackgroundDelegate()
{
	TutorialWidget->AddWidgetWidthValue(WidgetWidthAddValue);
	if (TutorialWidget->GetPadding().Left >= WidgetHalfWidthValue)
	{
		TutorialWidget->AddWidgetWidthValue(WidgetHalfWidthValue);
		GetWorldTimerManager().ClearTimer(BackgroundOpacityTimer);
	}
}

void APPTriggerWidgetBase::DisplayWidgetContentsDelegate()
{
	TutorialWidget->SetTutorialPanelOpacity(TutorialWidget->GetTutorialPanelOpacity() + WidgetOpacityAddValue);
	if (TutorialWidget->GetTutorialPanelOpacity() >= 1.0f)
	{
		TutorialWidget->SetTutorialPanelOpacity(1.0f);
		GetWorldTimerManager().ClearTimer(TutorialPanelOpacityTimer);
	}
}

void APPTriggerWidgetBase::HideWidgetContentsDelegate()
{
	TutorialWidget->SetTutorialPanelOpacity(TutorialWidget->GetTutorialPanelOpacity() - WidgetOpacityAddValue);
	if (TutorialWidget->GetTutorialPanelOpacity() <= 0.0f)
	{
		TutorialWidget->SetTutorialPanelOpacity(0.0f);
		GetWorldTimerManager().ClearTimer(TutorialPanelOpacityTimer);
		HideWidgetBackground();
	}
}

void APPTriggerWidgetBase::WidgetFocusOnPlayerDelegate()
{
	FVector LookVector = -OverlapActor->GetActorForwardVector();
	TutorialWidgetComponent->SetRelativeRotation(LookVector.Rotation());
}
