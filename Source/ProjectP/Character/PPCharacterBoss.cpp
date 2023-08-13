// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterBoss.h"
#include "ProjectP/AI/Boss/PPBossAIController.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "Math/UnrealMathUtility.h"
#include "ProjectP/BossGimmick/PPBGVineGardenData.h"
#include "ProjectP/BossGimmick/PPTentacle.h"
#include "ProjectP/Util/PPCollisionChannels.h"

APPCharacterBoss::APPCharacterBoss()
{
	// AIControllerClass = APPBossAIController::StaticClass();

	USkeletalMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"), EAssertionLevel::Check);
	GetMesh()->SetSkeletalMesh(MeshObj);

	VineGardenData = FPPConstructorHelper::FindAndGetObject<UPPBGVineGardenData>(TEXT("/Script/ProjectP.PPBGVineGardenData'/Game/DataAssets/Boss/GimmickVineGardenData.GimmickVineGardenData'"));

	VineGardenDamage = VineGardenData->Damage;
	TentacleNum = VineGardenData->TentacleNum;
	MinDistance = VineGardenData->MinDistance;
	MaxDistance = VineGardenData->MaxDistance;
	WarningFadeInDuration = VineGardenData->WarningFadeInDuration;
	WarningFadeOutDuration = VineGardenData->WarningFadeOutDuration;
	WarningDuration = VineGardenData->WarningDuration;
}

void APPCharacterBoss::SetupCharacterStatusData(UDataAsset* CharacterStatusData)
{

}

void APPCharacterBoss::BeginPlay()
{
	Super::BeginPlay();
	GenerateTentaclesOnRandomLocation(5);
}

void APPCharacterBoss::GenerateTentaclesOnRandomLocation(uint32 InNum)
{
	uint32 GeneratedNum = 0;
	while (GeneratedNum < InNum)
	{
		FVector2d RandomPont = FMath::RandPointInCircle(MaxDistance);
		const float Distance = FMath::RandRange(MinDistance, MaxDistance);
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
		SpawnedActor->ShowWarningSign(WarningFadeInDuration, WarningDuration, WarningFadeOutDuration, VineGardenDamage);

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
