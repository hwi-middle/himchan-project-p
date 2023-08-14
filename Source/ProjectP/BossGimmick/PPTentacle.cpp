// Fill out your copyright notice in the Description page of Project Settings.


#include "PPTentacle.h"

#include "PPBossGimmickData.h"
#include "PPWarningZoneCylinder.h"
#include "Engine/DamageEvents.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPTentacle::APPTentacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BossGimmickData = FPPConstructorHelper::FindAndGetObject<UPPBossGimmickData>(TEXT("/Script/ProjectP.PPBossGimmickData'/Game/DataAssets/Boss/BossGimmickData.BossGimmickData'"), EAssertionLevel::Check);
	Damage = BossGimmickData->VG_Damage;
	WarningFadeInDuration = BossGimmickData->VG_WarningFadeInDuration;
	WarningFadeOutDuration = BossGimmickData->VG_WarningFadeOutDuration;
	WarningDuration = BossGimmickData->VG_WarningDuration;
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

void APPTentacle::ShowWarningSign()
{
	WarningZone = GetWorld()->SpawnActor<APPWarningZoneCylinder>(GetActorLocation(), FRotator::ZeroRotator);
	WarningZone->Show(WarningFadeInDuration);
	GetWorldTimerManager().SetTimer(WarningTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		HideWarningSignAndAttack();
		GetWorldTimerManager().ClearTimer(WarningTimerHandle);
	}), WarningFadeInDuration + WarningDuration, false);
}

void APPTentacle::HideWarningSignAndAttack()
{
	if (WarningZone)
	{
		WarningZone->HideAndDestroy(WarningFadeOutDuration);
	}

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
				Player->TakeDamage(Damage, DamageEvent, nullptr, this);
			}
		}

		GetWorldTimerManager().ClearTimer(HitPlayerTimerHandle);
	}), WarningFadeOutDuration, false);
}