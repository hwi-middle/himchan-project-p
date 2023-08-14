// Fill out your copyright notice in the Description page of Project Settings.


#include "Leaf.h"

#include "PPBossGimmickData.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "TraceLog/standalone_epilogue.h"

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
	
	bIsActivated = false;
}

// Called when the game starts or when spawned
void ALeaf::BeginPlay()
{
	Super::BeginPlay();
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

	FHitResult HitResult;
	if (CheckPlayerWithSphere(50.f, HitResult))
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
	GetWorldTimerManager().SetTimer(BlinkTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		bIsActivated = true;
	}), TraceStartDelay, false);
}

void ALeaf::BlinkAndExplode()
{
	MaxBlinkSpeed = 4.0f;
	BlinkDuration = 1.0f;
	BlinkSpeed = 0.f;
	ElapsedTime = 0.f;
	UE_LOG(LogTemp, Log, TEXT("BlinkStart"));

	GetWorldTimerManager().SetTimer(BlinkTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		const float Alpha = ElapsedTime / BlinkDuration;
		if (Alpha >= 1.f)
		{
			FHitResult HitResult;
			if (CheckPlayerWithSphere(50.f, HitResult))
			{
				FDamageEvent DamageEvent;
				HitResult.GetActor()->TakeDamage(10.f, DamageEvent, nullptr, this);
			}

			GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
			Destroy();
		}

		BlinkSpeed = FMath::Lerp(0.f, MaxBlinkSpeed, Alpha);

		Mesh->SetScalarParameterValueOnMaterials(TEXT("BlinkSpeed"), BlinkSpeed);

		ElapsedTime += 0.01f;
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
