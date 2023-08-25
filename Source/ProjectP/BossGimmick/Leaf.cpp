// Fill out your copyright notice in the Description page of Project Settings.


#include "Leaf.h"

#include "PPBossGimmickData.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "ProjectP/Util/PPSoundData.h"
#include "ProjectP/Util/PPTimerHelper.h"

uint32 ALeaf::GlobalLeafNum = 0;

// Sets default values
ALeaf::ALeaf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeafMesh"));
	UStaticMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Project-P/Meshes/Environment/Boss/SM_Leaf.SM_Leaf'"));
	Mesh->SetStaticMesh(MeshObj);

	BossGimmickData = FPPConstructorHelper::FindAndGetObject<UPPBossGimmickData>(TEXT("/Script/ProjectP.PPBossGimmickData'/Game/DataAssets/Boss/BossGimmickData.BossGimmickData'"), EAssertionLevel::Check);
	Damage = BossGimmickData->LT_Damage;
	RotateSpeed = FMath::RandRange(BossGimmickData->LT_MinRotateSpeed, BossGimmickData->LT_MaxRotateSpeed);
	MoveSpeed = FMath::RandRange(BossGimmickData->LT_MinMoveSpeed, BossGimmickData->LT_MaxMoveSpeed);
	TraceStartDelay = BossGimmickData->LT_TraceStartDelay;
	TraceDuration = BossGimmickData->LT_TraceDuration;
	ElapsedTraceTime = 0.f;
	BlinkDuration = BossGimmickData->LT_BlinkDuration;
	MaxBlinkSpeed = BossGimmickData->LT_BlinkSpeed;
	FadeOutDuration = BossGimmickData->LT_FadeOutDuration;
	DetectRangeRadius = BossGimmickData->LT_DetectRangeRadius;
	ExplodeRangeRadius = BossGimmickData->LT_ExplodeRangeRadius;

	Tags.Add(TEXT("DestructibleObject"));
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
	Health = 0.1f;
	bIsActivated = false;
	bIsIgnored = false;
}

// Called when the game starts or when spawned
void ALeaf::BeginPlay()
{
	Super::BeginPlay();
	GlobalLeafNum++;
	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &ALeaf::ClearAllTimerOnLevelChange);

	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	DestroySoundCueArray = SoundData->BossLTDestroySoundCueArray;
	if (DestroySoundCueArray.IsEmpty())
	{
		USoundCue* TempSoundCue = nullptr;
		DestroySoundCueArray.Emplace(TempSoundCue);
	}
	ExplodeSoundCue = SoundData->BossLTExplodeSoundCue;

	Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ALeaf::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
	GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	GetWorldTimerManager().ClearTimer(DelayTracingTimerHandle);
	GetWorldTimerManager().ClearTimer(DestroyEffectTimerHandle);
	BlinkTimerHandle.Invalidate();
	DestroyTimerHandle.Invalidate();
	DelayTracingTimerHandle.Invalidate();
	DestroyEffectTimerHandle.Invalidate();
}

// Called every frame
void ALeaf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DrawDebugSphere(GetWorld(), GetActorLocation(), DetectRangeRadius, 16, FColor::Green, false, -1.f);
	// DrawDebugSphere(GetWorld(), GetActorLocation(), ExplodeRangeRadius, 16, FColor::Red, false, -1.f);

	if (!bIsActivated || !Target)
	{
		return;
	}

	ElapsedTraceTime += DeltaTime;

	FHitResult HitResult;
	if (ElapsedTraceTime > TraceDuration || CheckPlayerWithSphere(DetectRangeRadius, HitResult))
	{
		BlinkAndExplode();
		bIsActivated = false;
	}

	const FVector Direction = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	const FVector MissileForward = GetActorForwardVector();

	const FQuat TargetRotation = FQuat::Slerp(MissileForward.ToOrientationQuat(), Direction.ToOrientationQuat(), DeltaTime * RotateSpeed);

	SetActorRotation(TargetRotation.Rotator());
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * DeltaTime * MoveSpeed);
}

void ALeaf::StartTracing()
{
	GetWorldTimerManager().SetTimer(DelayTracingTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		bIsActivated = true;
		GetWorldTimerManager().ClearTimer(DelayTracingTimerHandle);
	}), TraceStartDelay, false);
}

void ALeaf::BlinkAndExplode()
{
	CurrentBlinkSpeed = 0.f;
	ElapsedBlinkTime = 0.f;

	GetWorldTimerManager().SetTimer(BlinkTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		const float Alpha = ElapsedBlinkTime / BlinkDuration;
		if (Alpha >= 1.f)
		{
			FHitResult HitResult;
			if (CheckPlayerWithSphere(ExplodeRangeRadius, HitResult))
			{
				FDamageEvent DamageEvent;
				HitResult.GetActor()->TakeDamage(Damage, DamageEvent, nullptr, this);
			}
			if(!bIsIgnored)
			{
				UGameplayStatics::PlaySound2D(this, ExplodeSoundCue);
			}
			GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
			FPPTimerHelper::InvalidateTimerHandle(BlinkTimerHandle);
			FadeOutAndDestroy();
			return;
		}

		CurrentBlinkSpeed = FMath::Lerp(0.f, MaxBlinkSpeed, Alpha);
		Mesh->SetScalarParameterValueOnMaterials(TEXT("BlinkSpeed"), CurrentBlinkSpeed);

		ElapsedBlinkTime += FPPTimerHelper::GetActualDeltaTime(BlinkTimerHandle);
	}), 0.01f, true);
}

bool ALeaf::CheckPlayerWithSphere(const float InRadius, FHitResult& Result)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_CHECK_PAWN,
		FCollisionShape::MakeSphere(InRadius),
		CollisionParams
	);

	if (!bHit)
	{
		return false;
	}

	const APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(Result.GetActor());
	return Player != nullptr;
}

void ALeaf::IncreaseHealth(const float Value)
{
	Health += Value;
}

void ALeaf::DecreaseHealth(const float Value)
{
	Health -= Value;
	if (Health <= 0)
	{
		if (GetWorldTimerManager().IsTimerActive(BlinkTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
		}
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DestroySoundCue = DestroySoundCueArray[FMath::RandRange(0, DestroySoundCueArray.Num() - 1)];
		UGameplayStatics::PlaySound2D(this, DestroySoundCue);
		bIsActivated = false;

		FadeOutAndDestroy();
	}
}

void ALeaf::FadeOutAndDestroy()
{
	ElapsedFadeOutTime = 0.f;
	Mesh->SetScalarParameterValueOnMaterials(TEXT("BlinkSpeed"), 0.f);

	GetWorldTimerManager().SetTimer(DestroyEffectTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		float CurrentOpacity = 0.0f;
		Mesh->GetMaterial(0)->GetScalarParameterValue(TEXT("Opacity"), CurrentOpacity);
		if (CurrentOpacity <= 0.0f)
		{
			GetWorldTimerManager().ClearTimer(DestroyEffectTimerHandle);
			GlobalLeafNum--;
			if (GlobalLeafNum == 0)
			{
				Boss->SetIsAttacking(false);
			}
			FPPTimerHelper::InvalidateTimerHandle(DestroyEffectTimerHandle);
			Destroy();
		}
		Mesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), FMath::Lerp(1.f, 0.f, ElapsedFadeOutTime / FadeOutDuration));
		ElapsedFadeOutTime += FPPTimerHelper::GetActualDeltaTime(DestroyEffectTimerHandle);
	}), 0.01f, true);
}
