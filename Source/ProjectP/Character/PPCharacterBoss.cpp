// Fill out your copyright notice in the Description page of Project Settings.

//  _____                     _                 _       _____  
// |  __ \                   (_)               | |     |  __ \
// | |__) |  _ __    ___      _    ___    ___  | |_    | |__) |
// |  ___/  | '__|  / _ \    | |  / _ \  / __| | __|   |  ___/ 
// | |      | |    | (_) |   | | |  __/ | (__  | |_    | |     
// |_|      |_|     \___/    | |  \___|  \___|  \__|   |_|     
// 							_/ |                               
// 						   |__/
//  _   _                             _____                               _           ______                                          _   _                 
// | \ | |                           / ____|                             (_)         |  ____|                                        | | (_)                
// |  \| |   ___    ___    _ __     | |  __    ___   _ __     ___   ___   _   ___    | |__    __   __   __ _   _ __     __ _    ___  | |  _    ___    _ __  
// | . ` |  / _ \  / _ \  | '_ \    | | |_ |  / _ \ | '_ \   / _ \ / __| | | / __|   |  __|   \ \ / /  / _` | | '_ \   / _` |  / _ \ | | | |  / _ \  | '_  \
// | |\  | |  __/ | (_) | | | | |   | |__| | |  __/ | | | | |  __/ \__ \ | | \__ \   | |____   \ V /  | (_| | | | | | | (_| | |  __/ | | | | | (_) | | | | |
// |_| \_|  \___|  \___/  |_| |_|    \_____|  \___| |_| |_|  \___| |___/ |_| |___/   |______|   \_/    \__,_| |_| |_|  \__, |  \___| |_| |_|  \___/  |_| |_|
// 																														__/ |                               
// 																													   |___/                                

#include "ProjectP/Character/PPCharacterBoss.h"

#include "NiagaraComponent.h"
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
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPCollisionChannels.h"

APPCharacterBoss::APPCharacterBoss()
{
	// AIControllerClass = APPBossAIController::StaticClass();

	USkeletalMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Project-P/Meshes/SkeletalMesh/Boss/boss_01.boss_01_Object515'"), EAssertionLevel::Check);
	GetMesh()->SetSkeletalMesh(MeshObj);

	BossData = FPPConstructorHelper::FindAndGetObject<UPPVRBossData>(TEXT("/Script/ProjectP.PPVRBossData'/Game/DataAssets/Boss/BossData.BossData'"), EAssertionLevel::Check);
	BossGimmickData = FPPConstructorHelper::FindAndGetObject<UPPBossGimmickData>(TEXT("/Script/ProjectP.PPBossGimmickData'/Game/DataAssets/Boss/BossGimmickData.BossGimmickData'"), EAssertionLevel::Check);
	bHasGFSpawned = false;

	GF_FX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("GreenFogFX"));
	UNiagaraSystem* GreenFogNiagaraSystem = FPPConstructorHelper::FindAndGetObject<UNiagaraSystem>(TEXT("/Script/Niagara.NiagaraSystem'/Game/Fantasy_Smoke_VFX/Effects/NS_Smoke_Sphere.NS_Smoke_Sphere'"), EAssertionLevel::Check);
	GF_FX->SetAsset(GreenFogNiagaraSystem);
	GF_FX->SetFloatParameter(TEXT("Sprite_Size"), 14.f);
	GF_FX->SetFloatParameter(TEXT("Sparks_Sprites_Amount"), 0.f);
	GF_FX->SetFloatParameter(TEXT("Smoke_Sprites_Amount"), 60.f);
	GF_FX->SetFloatParameter(TEXT("Sphere_radius"), BossGimmickData->GF_Radius);

	
}

void APPCharacterBoss::BeginPlay()
{
	Super::BeginPlay();
	GF_FX->SetActive(false);
	Health = BossData->MaxHP;

	VG_TentacleNum = BossGimmickData->VG_TentacleNum;
	VG_MinDistance = BossGimmickData->VG_MinDistance;
	VG_MaxDistance = BossGimmickData->VG_MaxDistance;

	LT_LeafNum = BossGimmickData->LT_LeafNum;

	GF_Damage = BossGimmickData->GF_Damage;
	GF_Duration = BossGimmickData->GF_Duration;
	GF_Radius = BossGimmickData->GF_Radius;

	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPCharacterBoss::ClearAllTimerOnLevelChange);

	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	VG_OmenSound = SoundData->BossVGOmenSoundCue;
	LT_OmenSound = SoundData->BossLTOmenSoundCue;
	GF_OmenSound = SoundData->BossGFOmenSoundCue;
	GF_SpawnSound = SoundData->BossGFSpawnSoundCue;

	GenerateToxicFog();
}

void APPCharacterBoss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GF_FX->SetWorldLocation(GetActorLocation());
}

void APPCharacterBoss::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(GreenFogTimerHandle);
	GreenFogTimerHandle.Invalidate();
}

void APPCharacterBoss::GenerateTentaclesOnRandomLocation(uint32 InNum)
{
	uint32 GeneratedNum = 0;
	UGameplayStatics::PlaySound2D(this, VG_OmenSound);
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
	UGameplayStatics::PlaySound2D(this, LT_OmenSound);
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
		ALeaf* SpawnedActor = GetWorld()->SpawnActor<ALeaf>(SpawnLocation, FRotator::ZeroRotator);
		SpawnedActor->StartTracing();

		++GeneratedNum;
	}
}

void APPCharacterBoss::GenerateToxicFog()
{
	GF_ElapsedTime = 0.f;
	UGameplayStatics::PlaySound2D(this, GF_OmenSound);
	GetWorldTimerManager().SetTimer(GreenFogTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		if (!bHasGFSpawned)
		{
			UGameplayStatics::PlaySound2D(this, GF_SpawnSound);
			GF_FX->SetActive(true);
			bHasGFSpawned = true;
		}

		if (GF_ElapsedTime >= GF_Duration)
		{
			FlushPersistentDebugLines(GetWorld());
			bHasGFSpawned = false;
			GetWorldTimerManager().ClearTimer(GreenFogTimerHandle);
			GF_FX->SetActive(false);
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
		// FlushPersistentDebugLines(GetWorld());
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
	if (Health <= 0)
	{
		// 테스트용 레벨 이동.
		// 최종 구현에서는 입구 반대편 문을 가리던 덩굴이 사라지는 기믹(기획팀이 그랬음)
		FString LevelName = UGameplayStatics::GetCurrentLevelName(this);
		if (LevelName == MAIN_LEVEL)
		{
			// 타이머 초기화 도중에 새로운 타이머 생성 방지
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			PlayerController->SetIgnoreMoveInput(true);
			PlayerController->SetIgnoreLookInput(true);
			GetWorld()->GetGameInstanceChecked<UPPGameInstance>()->ClearAllTimerHandle();
			UGameplayStatics::OpenLevel(this, ENDING_LEVEL);
		}
	}
}

void APPCharacterBoss::TestPattern(EBossPattern Pattern)
{
	switch (Pattern)
	{
	case EBossPattern::GreenFog:
		GenerateToxicFog();
		break;
	case EBossPattern::LeafTempest:
		GenerateLeafTempestOnRandomLocation(LT_LeafNum);
		break;
	case EBossPattern::VineGarden:
		GenerateTentaclesOnRandomLocation(VG_TentacleNum);
		break;
	default:
		checkNoEntry();
	}
}
