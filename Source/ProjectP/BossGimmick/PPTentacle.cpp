// Fill out your copyright notice in the Description page of Project Settings.


#include "PPTentacle.h"

#include "PPWarningZoneCylinder.h"
#include "Engine/DamageEvents.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Util/PPCollisionChannels.h"

// Sets default values
APPTentacle::APPTentacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void APPTentacle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APPTentacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPTentacle::ShowWarningSign(float InFadeInDuration, float InDelay, float InFadeOutDuration, float InDamage)
{
	Damage = InDamage;
	WarningZone = GetWorld()->SpawnActor<APPWarningZoneCylinder>(GetActorLocation(), FRotator::ZeroRotator);
	WarningZone->Show(InFadeInDuration);
	FadeOutDuration = InFadeOutDuration;
	GetWorldTimerManager().SetTimer(WarningTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		HideWarningSignAndAttack(FadeOutDuration, InDamage);
		GetWorldTimerManager().ClearTimer(WarningTimerHandle);
	}), InFadeInDuration + InDelay, false);
}

void APPTentacle::HideWarningSignAndAttack(float InFadeOutDuration, float InDamage)
{
	if (WarningZone)
	{
		WarningZone->HideAndDestroy(InFadeOutDuration);
	}
	UE_LOG(LogTemp, Log, TEXT("촉수 사라짐"));

	// TODO: 촉수 나오는 애니메이션 재생
	GetWorldTimerManager().SetTimer(HitPlayerTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			GetActorLocation(),
			GetActorLocation(),
			FQuat::Identity,
			ECC_CHECK_PAWN,
			FCollisionShape::MakeSphere(50.f),
			CollisionParams
		);

		if (bHit)
		{
			APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(HitResult.GetActor());
			if (Player)
			{
				FDamageEvent DamageEvent;
				Player->TakeDamage(InDamage, DamageEvent, nullptr, this);
			}
		}

		GetWorldTimerManager().ClearTimer(HitPlayerTimerHandle);
	}), InFadeOutDuration, false);
}