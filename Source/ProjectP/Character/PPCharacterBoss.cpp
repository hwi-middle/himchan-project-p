// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterBoss.h"

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

	USkeletalMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"), EAssertionLevel::Check);
	GetMesh()->SetSkeletalMesh(MeshObj);

	BossGimmickData = FPPConstructorHelper::FindAndGetObject<UPPBossGimmickData>(TEXT("/Script/ProjectP.PPBossGimmickData'/Game/DataAssets/Boss/BossGimmickData.BossGimmickData'"), EAssertionLevel::Check);

	VG_Damage = BossGimmickData->VG_Damage;
	VG_TentacleNum = BossGimmickData->VG_TentacleNum;
	VG_MinDistance = BossGimmickData->VG_MinDistance;
	VG_MaxDistance = BossGimmickData->VG_MaxDistance;
	VG_WarningFadeInDuration = BossGimmickData->VG_WarningFadeInDuration;
	VG_WarningFadeOutDuration = BossGimmickData->VG_WarningFadeOutDuration;
	VG_WarningDuration = BossGimmickData->VG_WarningDuration;

	LT_LeafNum = BossGimmickData->LT_LeafNum;
}

void APPCharacterBoss::SetupCharacterStatusData(UDataAsset* CharacterStatusData)
{

}

void APPCharacterBoss::BeginPlay()
{
	Super::BeginPlay();
	GenerateLeafTempestOnRandomLocation(5);
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
			continue;
		}

		// 액터 스폰
		APPTentacle* SpawnedActor = GetWorld()->SpawnActor<APPTentacle>(SpawnLocation, FRotator::ZeroRotator);
		SpawnedActor->ShowWarningSign(VG_WarningFadeInDuration, VG_WarningDuration, VG_WarningFadeOutDuration, VG_Damage);

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
