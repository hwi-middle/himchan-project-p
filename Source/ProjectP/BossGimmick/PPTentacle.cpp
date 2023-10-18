// Fill out your copyright notice in the Description page of Project Settings.


#include "PPTentacle.h"

#include "PPBossGimmickData.h"
#include "PPWarningZoneCylinder.h"
#include "Engine/DamageEvents.h"
#include "ProjectP/Animation/PPTentacleAnimInstance.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "ProjectP/Util/PPTimerHelper.h"

// Sets default values
APPTentacle::APPTentacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BossGimmickData = FPPConstructorHelper::FindAndGetObject<UPPBossGimmickData>(TEXT("/Script/ProjectP.PPBossGimmickData'/Game/DataAssets/Boss/BossGimmickData.BossGimmickData'"), EAssertionLevel::Check);

	TentacleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	USkeletalMesh* Mesh = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Project-P/Meshes/SkeletalMesh/BossTentacle/Meshs/SK_Tentacle_Start.SK_Tentacle_Start'"), EAssertionLevel::Check);
	TentacleMesh->SetSkeletalMesh(Mesh);

	const TSubclassOf<UPPTentacleAnimInstance> HandAnimInstanceClass = FPPConstructorHelper::FindAndGetClass<UPPTentacleAnimInstance>(
		TEXT("/Game/Project-P/Meshes/SkeletalMesh/BossTentacle/Animation/Misc/ABP_TentacleAnimInstance.ABP_TentacleAnimInstance_C"), EAssertionLevel::Check);
	TentacleMesh->SetAnimInstanceClass(HandAnimInstanceClass);
	TentacleMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	RootComponent = TentacleMesh;
}

// Called when the game starts or when spawned
void APPTentacle::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UPPTentacleAnimInstance>(TentacleMesh->GetAnimInstance());

	Damage = BossGimmickData->VG_Damage;
	WarningFadeInDuration = BossGimmickData->VG_WarningFadeInDuration;
	WarningFadeOutDuration = BossGimmickData->VG_WarningFadeOutDuration;
	WarningDuration = BossGimmickData->VG_WarningDuration;
	DamageRadius = BossGimmickData->VG_DamageRadius;

	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPTentacle::ClearAllTimerOnLevelChange);

	// float TempAnimationDuration = 0.5f; // 임시 값
	// float DebugSphereLifeTime = WarningDuration + WarningFadeInDuration + WarningFadeOutDuration + TempAnimationDuration;
	// DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 16, FColor::Red, false, DebugSphereLifeTime);
}

void APPTentacle::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(WarningTimerHandle);
	GetWorldTimerManager().ClearTimer(HitPlayerTimerHandle);
	WarningTimerHandle.Invalidate();
	HitPlayerTimerHandle.Invalidate();
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
	GetWorldTimerManager().SetTimer(WarningTimerHandle, this, &APPTentacle::ShowWarningSignDelegate, WarningFadeInDuration + WarningDuration, false);
}

void APPTentacle::HideWarningSignAndAttack()
{
	if (WarningZone)
	{
		WarningZone->HideAndDestroy(WarningFadeOutDuration);
	}

	GetWorldTimerManager().SetTimer(HitPlayerTimerHandle, this, &APPTentacle::HideWarningSignAndAttackDelegate, WarningFadeOutDuration, false);


}

void APPTentacle::HideTentacle()
{
	GetWorldTimerManager().SetTimer(HitPlayerTimerHandle, this, &APPTentacle::HideTentacleDelegate, 0.01f, true);
}

void APPTentacle::DestroyTentacle()
{
	GetWorldTimerManager().SetTimer(HitPlayerTimerHandle, this, &APPTentacle::DestroyTentacleDelegate, 0.01f, true);
}

//----------------------------Delegates------------------------
void APPTentacle::ShowWarningSignDelegate()
{
	HideWarningSignAndAttack();
	GetWorldTimerManager().ClearTimer(WarningTimerHandle);
}

void APPTentacle::HideWarningSignAndAttackDelegate()
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PLAYER,
		FCollisionShape::MakeSphere(DamageRadius),
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

		GetWorldTimerManager().ClearTimer(HitPlayerTimerHandle);
		return;
	}
	AnimInstance->Show();
	GetWorldTimerManager().ClearTimer(HitPlayerTimerHandle);
	HideTentacle();
}

void APPTentacle::HideTentacleDelegate()
{
	if (!FPPTimerHelper::IsDelayElapsed(HitPlayerTimerHandle, 1.4f))
	{
		return;
	}
	AnimInstance->Hide();
	GetWorldTimerManager().ClearTimer(HitPlayerTimerHandle);
	FPPTimerHelper::InvalidateTimerHandle(HitPlayerTimerHandle);
	DestroyTentacle();
}

void APPTentacle::DestroyTentacleDelegate()
{
	if (!FPPTimerHelper::IsDelayElapsed(HitPlayerTimerHandle, 2.0f))
	{
		return;
	}
	GetWorldTimerManager().ClearTimer(HitPlayerTimerHandle);
	FPPTimerHelper::InvalidateTimerHandle(HitPlayerTimerHandle);
	Boss->SetIsAttacking(false);
	Destroy();
}
