// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterBoss.h"

#include "PPCharacterPlayer.h"
#include "PPVRBossData.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/AI/Boss/PPBossAIController.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "Math/UnrealMathUtility.h"
#include "ProjectP/BossGimmick/Leaf.h"
#include "ProjectP/BossGimmick/PPBossGimmickData.h"
#include "ProjectP/BossGimmick/PPTentacle.h"
#include "ProjectP/Util/PPCollisionChannels.h"

APPCharacterBoss::APPCharacterBoss()
{
	// AIControllerClass = APPBossAIController::StaticClass();

	// USkeletalMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"), EAssertionLevel::Check);
	// GetMesh()->SetSkeletalMesh(MeshObj);
	
	UStaticMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/30-Level-Design/Meshes/Boss/himchan_v01_Group12084.himchan_v01_Group12084'"), EAssertionLevel::Check);
	TempMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentFuckingTemporal"));
	TempMesh->SetStaticMesh(MeshObj);
	RootComponent = TempMesh;

	BossData = FPPConstructorHelper::FindAndGetObject<UPPVRBossData>(TEXT("/Script/ProjectP.PPVRBossData'/Game/DataAssets/Boss/BossData.BossData'"), EAssertionLevel::Check);
	BossGimmickData = FPPConstructorHelper::FindAndGetObject<UPPBossGimmickData>(TEXT("/Script/ProjectP.PPBossGimmickData'/Game/DataAssets/Boss/BossGimmickData.BossGimmickData'"), EAssertionLevel::Check);
}

void APPCharacterBoss::BeginPlay()
{
	Super::BeginPlay();

	Health = BossData->MaxHP;
	
	VG_TentacleNum = BossGimmickData->VG_TentacleNum;
	VG_MinDistance = BossGimmickData->VG_MinDistance;
	VG_MaxDistance = BossGimmickData->VG_MaxDistance;

	LT_LeafNum = BossGimmickData->LT_LeafNum;

	GF_Damage = BossGimmickData->GF_Damage;
	GF_Duration = BossGimmickData->GF_Duration;
	GF_Radius = BossGimmickData->GF_Radius;
}

void APPCharacterBoss::GenerateTentaclesOnRandomLocation(uint32 InNum)
{
	uint32 GeneratedNum = 0;
	while (GeneratedNum < InNum)
	{
		FVector2d RandomPont = FMath::RandPointInCircle(VG_MaxDistance);
		const float Distance = FMath::RandRange(VG_MinDistance, VG_MaxDistance);
		RandomPont.Normalize();
		RandomPont *= Distance;

		FVector SpawnLocation = FVector(RandomPont.X, RandomPont.Y, 0.f) + GetActorLocation();
		SpawnLocation.Z = 0.f;

		// 환경과 충돌이 있는지 검사
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			SpawnLocation,
			SpawnLocation,
			FQuat::Identity,
			ECC_ENVIRONMENT,
			FCollisionShape::MakeSphere(50.f),
			CollisionParams
		);

		// 환경과 충돌이 있었다면 스폰하지 않고 다시 위치 생성
		if (bHit)
		{
			UE_LOG(LogTemp, Log, TEXT("%s과 충돌"), *HitResult.GetActor()->GetName());
			continue;
		}

		// 액터 스폰
		APPTentacle* SpawnedActor = GetWorld()->SpawnActor<APPTentacle>(SpawnLocation, FRotator::ZeroRotator);
		SpawnedActor->ShowWarningSign();

		++GeneratedNum;
	}
}

void APPCharacterBoss::GenerateLeafTempestOnRandomLocation(uint32 InNum)
{
	uint32 GeneratedNum = 0;
	while (GeneratedNum < InNum)
	{
		FVector2d RandomPont = FMath::RandPointInCircle(VG_MaxDistance);
		const float Distance = FMath::RandRange(VG_MinDistance, VG_MaxDistance);
		RandomPont.Normalize();
		RandomPont *= Distance;

		FVector SpawnLocation = FVector(RandomPont.X, RandomPont.Y, 0.f) + GetActorLocation();
		SpawnLocation.Z = 500.f;

		// 환경과 충돌이 있는지 검사
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			SpawnLocation,
			SpawnLocation,
			FQuat::Identity,
			ECC_ENVIRONMENT,
			FCollisionShape::MakeSphere(50.f),
			CollisionParams
		);

		// 환경과 충돌이 있었다면 스폰하지 않고 다시 위치 생성
		if (bHit)
		{
			continue;
		}

		// 액터 스폰
		FTransform Transform(FQuat::Identity, SpawnLocation);
		ALeaf* SpawnedActor = GetWorld()->SpawnActor<ALeaf>(SpawnLocation, FRotator::ZeroRotator);
		SpawnedActor->StartTracing();

		++GeneratedNum;
	}
}

void APPCharacterBoss::GenerateToxicFog()
{
	GF_ElapsedTime = 0.f;
	GetWorldTimerManager().SetTimer(GreenFogTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		if (GF_ElapsedTime >= GF_Duration)
		{
			GetWorldTimerManager().ClearTimer(GreenFogTimerHandle);
			return;
		}

		FVector SpawnLocation = GetActorLocation();
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			SpawnLocation,
			SpawnLocation,
			FQuat::Identity,
			ECC_CHECK_PAWN,
			FCollisionShape::MakeSphere(GF_Radius),
			CollisionParams
		);
		// TestOnly
		FlushPersistentDebugLines(GetWorld());
		DrawDebugSphere(GetWorld(), GetActorLocation(), GF_Radius, 64, FColor::Green, false, 1.f);
		//
		GF_ElapsedTime += 1.f;
		if (!bHit)
		{
			return;
		}

		APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(HitResult.GetActor());
		if (!Player)
		{
			return;
		}
		
		FDamageEvent DamageEvent;
		Player->TakeDamage(GF_Damage, DamageEvent, nullptr, this);
	}), 1.f, true, 0.f);
}

void APPCharacterBoss::IncreaseHealth(const float Value)
{
	/*
	 * Do something
	 */
	Health += Value;
}

void APPCharacterBoss::DecreaseHealth(const float Value)
{
	/*
	 * Do something
	 */
	Health -= Value;
}

void APPCharacterBoss::TestPattern(EBossPattern Pattern, uint32 Num)
{
	switch (Pattern)
	{
	case EBossPattern::GreenFog:
		GenerateToxicFog();
		break;
	case EBossPattern::LeafTempest:
		GenerateLeafTempestOnRandomLocation(Num);
		break;
	case EBossPattern::VineGarden:
		GenerateTentaclesOnRandomLocation(Num);
		break;
	default:
		checkNoEntry();
	}
}
