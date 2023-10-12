// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/UI/Prologue/PPPrologueActor.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/StringDataTable.h"

class UPPGameInstance;
// Sets default values
APPPrologueActor::APPPrologueActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrologueWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PrologueWidget"));
	NextArrayNum = 0;
	HandleChangeTime = 0;
}

// Called when the game starts or when spawned
void APPPrologueActor::BeginPlay()
{
	Super::BeginPlay();
	
	PostProcessVolume = Cast<APostProcessVolume>(GetWorld()->PostProcessVolumes[0]);
	if(PrologueStringDataHandle.IsEmpty())
	{
		FDataTableRowHandle TableRowHandle;
		PrologueStringDataHandle.Emplace(TableRowHandle);
	}
	PrologueWidget = Cast<UPPPrologueWidget>(PrologueWidgetComponent->GetUserWidgetObject());
	const FStringDataTable* PrologueString = PrologueStringDataHandle[0].GetRow<FStringDataTable>(PrologueStringDataHandle[0].RowName.ToString());
	FText PrologueText = FText::FromName(PrologueString->Kor);
	PrologueWidget->SetPrologueText(PrologueText);
	NextArrayNum = 1;
	
	const TObjectPtr<UPPGameInstance> GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPPrologueActor::ClearAllTimerOnLevelChange);
	
	DisplayStringData();
}

void APPPrologueActor::ClearAllTimerOnLevelChange()
{
	GetWorld()->GetTimerManager().ClearTimer(StringDataChangeTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(LoadMainLevelTimerHandle);
	StringDataChangeTimerHandle.Invalidate();
	LoadMainLevelTimerHandle.Invalidate();
}

void APPPrologueActor::DisplayStringData()
{
	GetWorldTimerManager().SetTimer(StringDataChangeTimerHandle, this, APPPrologueActor::DisplayStringDataDelegate, HandleChangeTime, true, HandleChangeTime);
}

void APPPrologueActor::LoadMainLevelSequence()
{
	DisableInput(GetWorld()->GetFirstPlayerController());
	GetWorldTimerManager().SetTimer(LoadMainLevelTimerHandle, this, APPPrologueActor::LoadMainLevelDelegate, 0.01f, true, HandleChangeTime);
}

//------------------------------------------Delegates--------------------------------------
void APPPrologueActor::DisplayStringDataDelegate()
{
	const FStringDataTable* PrologueString = PrologueStringDataHandle[NextArrayNum].GetRow<FStringDataTable>(PrologueStringDataHandle[NextArrayNum].RowName.ToString());
	FText PrologueText = FText::FromName(PrologueString->Kor);
	PrologueWidget->SetPrologueText(PrologueText);
	NextArrayNum++;
	if (NextArrayNum >= PrologueStringDataHandle.Num())
	{
		LoadMainLevelSequence();
		GetWorldTimerManager().ClearTimer(StringDataChangeTimerHandle);
	}
}

void APPPrologueActor::LoadMainLevelDelegate()
{
	if (PostProcessVolume->Settings.AutoExposureBias <= -5.0f && PostProcessVolume->Settings.VignetteIntensity >= 2.5f)
	{
		GetWorldTimerManager().ClearTimer(LoadMainLevelTimerHandle);
		GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
		UGameplayStatics::OpenLevel(GetWorld(), MAIN_LEVEL);
		return;
	}
	PostProcessVolume->Settings.AutoExposureBias -= 0.02f;
	PostProcessVolume->Settings.VignetteIntensity += 0.01f;
}

// Called every frame
void APPPrologueActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

