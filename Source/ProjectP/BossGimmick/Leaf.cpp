// Fill out your copyright notice in the Description page of Project Settings.


#include "Leaf.h"

#include "PPBossGimmickData.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "ProjectP/Util/PPSoundData.h"

// Sets default values
ALeaf::ALeaf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeafMesh"));
	UStaticMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Project-P/Material/BossGimmick/Leaf/SM_Cube.SM_Cube'"));
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
	DestroySpeed = BossGimmickData->LT_DestroySpeed;
	
	Tags.Add(TEXT("DestructibleObject"));
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
	Health = 0.1f;
	bIsActivated = false;
}

// Called when the game starts or when spawned
void ALeaf::BeginPlay()
{
	Super::BeginPlay();
	
	const UPPSoundData* SoundData = GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->GetSoundData();
	ExplodeSoundCue = SoundData->BossLeafTempestExplodeSoundCue;
	DestroySoundCue = SoundData->BossLeafTempestDestroySoundCue;
	
	Target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void ALeaf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActivated || !Target)
	{
		return;
	}

	ElapsedTraceTime += DeltaTime;

	FHitResult HitResult;
	if (ElapsedTraceTime > TraceDuration || CheckPlayerWithSphere(50.f, HitResult))
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
			if (CheckPlayerWithSphere(50.f, HitResult))
			{
				FDamageEvent DamageEvent;
				HitResult.GetActor()->TakeDamage(10.f, DamageEvent, nullptr, this);
			}
			UGameplayStatics::PlaySound2D(this, ExplodeSoundCue);
			GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
			Destroy();
		}

		CurrentBlinkSpeed = FMath::Lerp(0.f, MaxBlinkSpeed, Alpha);
		Mesh->SetScalarParameterValueOnMaterials(TEXT("BlinkSpeed"), CurrentBlinkSpeed);

		ElapsedBlinkTime += 0.01f;
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
		if(GetWorldTimerManager().IsTimerActive(BlinkTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
		}
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UGameplayStatics::PlaySound2D(this, DestroySoundCue);
		bIsActivated = false;
		
		GetWorldTimerManager().SetTimer(DestroyEffectTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			float CurrentOpacity = 0.0f;
			Mesh->GetMaterial(0)->GetScalarParameterValue(TEXT("Opacity"), CurrentOpacity);
			if(CurrentOpacity <= 0.0f)
			{
				GetWorldTimerManager().ClearTimer(DestroyEffectTimerHandle);
				Destroy();
			}
			Mesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), CurrentOpacity - DestroySpeed);
		}), 0.01f, true);
	}
}
