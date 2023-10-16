// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Ending/PPEndingScreenBaseActor.h"

#include "PPEndingUIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"

// Sets default values
APPEndingScreenBaseActor::APPEndingScreenBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	EndingScreenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScreenWidget"));
	RootComponent = EndingScreenWidgetComponent;
	ScreenLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("ScreenLight"));
	ScreenLight->SetIntensityUnits(ELightUnits::Candelas);
	ScreenLight->SetupAttachment(RootComponent);
	ScreenLight->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	TimerTick = 0.1f;
}


// Called every frame
void APPEndingScreenBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void APPEndingScreenBaseActor::BeginPlay()
{
	Super::BeginPlay();

	EndingUIWidget = CastChecked<UPPEndingUIWidget>(EndingScreenWidgetComponent->GetUserWidgetObject());
	if(EndingUIWidget)
	{
		EndingUIWidget->SetScreenOpacity(0.0f);
	}
	
	ScreenLight->SetIntensity(0.0f);
	ToggleLight(false);

	const FStringDataTable* EndingString = PrologueStringDataHandle[0].GetRow<FStringDataTable>(PrologueStringDataHandle[0].RowName.ToString());
	FText EndingText = FText::FromName(EndingString->Kor);
	EndingUIWidget->SetEndingText(EndingText);
	NextArrayNum = 1;
	
	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPEndingScreenBaseActor::ClearAllTimerOnLevelChange);
}

void APPEndingScreenBaseActor::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(FadeSequenceTimer);
	GetWorldTimerManager().ClearTimer(CreditMoveTimer);
	GetWorldTimerManager().ClearTimer(DelayTimer);
	GetWorldTimerManager().ClearTimer(LightIntensityControlTimer);
	FadeSequenceTimer.Invalidate();
	CreditMoveTimer.Invalidate();
	DelayTimer.Invalidate();
	LightIntensityControlTimer.Invalidate();
}

void APPEndingScreenBaseActor::FadeInOrOutScreenImage(const bool IsFaded)
{
	EndingUIWidget = Cast<UPPEndingUIWidget>(EndingScreenWidgetComponent->GetUserWidgetObject());
	if(IsFaded)
	{
		GetWorldTimerManager().SetTimer(FadeSequenceTimer, this, &APPEndingScreenBaseActor::FadeInScreenImageDelegate, TimerTick, true);
	}
	else
	{
		GetWorldTimerManager().SetTimer(FadeSequenceTimer, this, &APPEndingScreenBaseActor::FadeOutScreenImageDelegate, TimerTick, true);
	}
}

void APPEndingScreenBaseActor::ActivateCreditPanel()
{
	GetWorldTimerManager().SetTimer(FadeSequenceTimer, this, &APPEndingScreenBaseActor::ActivateCreditPanelDelegate, TimerTick, true);
}

void APPEndingScreenBaseActor::MoveCreditPanel()
{
	GetWorldTimerManager().SetTimer(CreditMoveTimer, this, &APPEndingScreenBaseActor::MoveCreditPanelDelegate, 0.01f, true);
}

void APPEndingScreenBaseActor::ExitToLobby()
{
	GetWorldTimerManager().SetTimer(DelayTimer, this, &APPEndingScreenBaseActor::ExitToLobbyDelegate, ExitToLobbyDelay, false);
}

void APPEndingScreenBaseActor::EnableAutoFadeTimer()
{
	GetWorldTimerManager().SetTimer(DelayTimer, this, &APPEndingScreenBaseActor::EnableAutoFadeTimerDelegate, AutoFadeTime, false);
}

void APPEndingScreenBaseActor::ToggleLight(bool IsEnable)
{
	if(!IsEnable)
	{
		GetWorldTimerManager().SetTimer(LightIntensityControlTimer, this, &APPEndingScreenBaseActor::ToggleLightOnAndEndingImageSettingDelegate, TimerTick, true);
	}
	else
	{
		GetWorldTimerManager().SetTimer(LightIntensityControlTimer, this, &APPEndingScreenBaseActor::ToggleLightOffDelegate, TimerTick, true);
	}
}

void APPEndingScreenBaseActor::FadeInScreenImageDelegate()
{
	EndingUIWidget->SetScreenOpacity(EndingUIWidget->GetScreenOpacity() + TimerTick / ImageFadeSequenceTime);
	if (EndingUIWidget->GetScreenOpacity() >= 1.0f)
	{
		EndingUIWidget->SetScreenOpacity(1.0f);
		GetWorldTimerManager().ClearTimer(FadeSequenceTimer);
		EnableAutoFadeTimer();
	}
}

void APPEndingScreenBaseActor::FadeOutScreenImageDelegate()
{
	EndingUIWidget->SetScreenOpacity(EndingUIWidget->GetScreenOpacity() - TimerTick / ImageFadeSequenceTime);
	if (EndingUIWidget->GetScreenOpacity() <= 0.0f)
	{
		EndingUIWidget->SetScreenOpacity(0.0f);
		GetWorldTimerManager().ClearTimer(FadeSequenceTimer);

		bool CheckRemainImage = EndingUIWidget->SetScreenImage(EndingUIWidget->GetCurrentScreenImageNum() + 1);
		if (CheckRemainImage)
		{
			FadeInOrOutScreenImage(true);
		}
		else
		{
			MaxCreditBottomPosition = EndingUIWidget->GetCreditHeight();
			FText EndingText = FText::FromString(TEXT(""));
			EndingUIWidget->SetEndingText(EndingText);
			ActivateCreditPanel();
			return;
		}
		const FStringDataTable* EndingString = PrologueStringDataHandle[NextArrayNum].GetRow<FStringDataTable>(PrologueStringDataHandle[NextArrayNum].RowName.ToString());
		FText EndingText = FText::FromName(EndingString->Kor);
		EndingUIWidget->SetEndingText(EndingText);
		NextArrayNum++;
	}
}

void APPEndingScreenBaseActor::ActivateCreditPanelDelegate()
{
	EndingUIWidget->SetCreditOpacity(EndingUIWidget->GetCreditOpacity() + TimerTick / ImageFadeSequenceTime);
	if (EndingUIWidget->GetCreditOpacity() >= 1.0f)
	{
		EndingUIWidget->SetCreditOpacity(1.0f);
		GetWorldTimerManager().ClearTimer(FadeSequenceTimer);
		MoveCreditPanel();
	}
}

void APPEndingScreenBaseActor::MoveCreditPanelDelegate()
{
	float CreditPosition = EndingUIWidget->AddCreditPosition(-CreditAddPositionValue);
	if (CreditPosition <= -MaxCreditBottomPosition)
	{
		GetWorldTimerManager().ClearTimer(CreditMoveTimer);
		ToggleLight(true);
		ExitToLobby();
	}
}

void APPEndingScreenBaseActor::ExitToLobbyDelegate()
{
	GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
	UGameplayStatics::OpenLevel(this, LOBBY_LEVEL);
}

void APPEndingScreenBaseActor::EnableAutoFadeTimerDelegate()
{
	FadeInOrOutScreenImage(false);
	GetWorldTimerManager().ClearTimer(DelayTimer);
}

void APPEndingScreenBaseActor::ToggleLightOnAndEndingImageSettingDelegate()
{
	ScreenLight->SetIntensity(ScreenLight->Intensity + LightEnhanceIntensityPerTick);
	if (ScreenLight->Intensity >= LightMaxIntensity)
	{
		ScreenLight->SetIntensity(LightMaxIntensity);
		GetWorldTimerManager().ClearTimer(LightIntensityControlTimer);
		// 엔딩 이미지 재생 시작.
		FadeInOrOutScreenImage(true);
	}
}

void APPEndingScreenBaseActor::ToggleLightOffDelegate()
{
	ScreenLight->SetIntensity(ScreenLight->Intensity - LightEnhanceIntensityPerTick);
	if (ScreenLight->Intensity <= 0.0f)
	{
		ScreenLight->SetIntensity(0.0f);
		GetWorldTimerManager().ClearTimer(LightIntensityControlTimer);
	}
}

