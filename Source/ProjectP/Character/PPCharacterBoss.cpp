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
#include "PPBossCore.h"
#include "PPCharacterPlayer.h"
#include "PPVRBossData.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Util/PPConstructorHelper.h"
#include "Math/UnrealMathUtility.h"
#include "ProjectP/BossGimmick/Leaf.h"
#include "ProjectP/BossGimmick/PPBossGimmickData.h"
#include "ProjectP/BossGimmick/PPTentacle.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Animation/PPBossAnimInstance.h"
#include "ProjectP/Util/PPTimerHelper.h"

APPCharacterBoss::APPCharacterBoss()
{
	// AIControllerClass = APPBossAIController::StaticClass();

	USkeletalMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Project-P/Meshes/SkeletalMesh/BossBody/Meshs/SK_Boss_Idle_2.SK_Boss_Idle_2'"), EAssertionLevel::Check);
	GetMesh()->SetSkeletalMesh(MeshObj);

	BossData = FPPConstructorHelper::FindAndGetObject<UPPVRBossData>(TEXT("/Script/ProjectP.PPVRBossData'/Game/DataAssets/Boss/BossData.BossData'"), EAssertionLevel::Check);
	BossGimmickData = FPPConstructorHelper::FindAndGetObject<UPPBossGimmickData>(TEXT("/Script/ProjectP.PPBossGimmickData'/Game/DataAssets/Boss/BossGimmickData.BossGimmickData'"), EAssertionLevel::Check);
	bHasGFSpawned = false;

	GF_FX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("GreenFogFX"));
	GF_FX->SetupAttachment(RootComponent);
	UNiagaraSystem* GreenFogNiagaraSystem = FPPConstructorHelper::FindAndGetObject<UNiagaraSystem>(TEXT("/Script/Niagara.NiagaraSystem'/Game/Fantasy_Smoke_VFX/Effects/NS_Smoke_Sphere.NS_Smoke_Sphere'"), EAssertionLevel::Check);
	GF_FX->SetAsset(GreenFogNiagaraSystem);
	GF_FX->SetFloatParameter(TEXT("Sprite_Size"), 14.f);
	GF_FX->SetFloatParameter(TEXT("Sparks_Sprites_Amount"), 0.f);
	GF_FX->SetFloatParameter(TEXT("Smoke_Sprites_Amount"), 60.f);
	GF_FX->SetFloatParameter(TEXT("Sphere_radius"), BossGimmickData->GF_Radius);

	const TSubclassOf<UPPBossAnimInstance> BossAnimInstanceClass = FPPConstructorHelper::FindAndGetClass<UPPBossAnimInstance>(
		TEXT("/Game/Project-P/Meshes/SkeletalMesh/BossBody/Animation/Misc/ABP_Boss.ABP_Boss_C"), EAssertionLevel::Check);
	GetMesh()->SetAnimInstanceClass(BossAnimInstanceClass);

	Tags.Add(TEXT("DestructibleObject"));
}

void APPCharacterBoss::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionProfileName(CP_ENEMY);
	
	Core = GetWorld()->SpawnActor<APPBossCore>(AActor::GetTargetLocation() + FVector(0.f, 0.f, 14.f), FRotator::ZeroRotator);
	Core->SetBoss(this);
	bIsAttacking = false;
	GF_FX->Deactivate();
	Health = BossData->MaxHP;

	VG_TentacleNum = BossGimmickData->VG_TentacleNum;
	VG_MinDistance = BossGimmickData->VG_MinDistance;
	VG_MaxDistance = BossGimmickData->VG_MaxDistance;

	LT_LeafNum = BossGimmickData->LT_LeafNum;

	GF_Damage = BossGimmickData->GF_Damage;
	GF_Duration = BossGimmickData->GF_Duration;
	GF_Radius = BossGimmickData->GF_Radius;

	AttackDelayMin = BossGimmickData->AttackDelayMin;
	AttackDelayMax = BossGimmickData->AttackDelayMax;
	AttackDelay = FMath::RandRange(AttackDelayMin, AttackDelayMax);
	ElapsedAttackDelay = 0;
	PreviousPattern = GetRandomPattern();

	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	GameInstance->ClearTimerHandleDelegate.AddUObject(this, &APPCharacterBoss::ClearAllTimerOnLevelChange);

	const UPPSoundData* SoundData = GameInstance->GetSoundData();
	USoundCue* TempSoundCue;
	VG_OmenSound = SoundData->BossVGOmenSoundCue;
	LT_OmenSound = SoundData->BossLTOmenSoundCue;
	GF_OmenSound = SoundData->BossGFOmenSoundCue;
	GF_SpawnSound = SoundData->BossGFSpawnSoundCue;

	VG_CommanderSoundCueArray = SoundData->CommanderVGWaringSoundCueArray;
	if (VG_CommanderSoundCueArray.IsEmpty())
	{
		VG_CommanderSoundCueArray.Emplace(TempSoundCue);
	}
	LT_CommanderSoundCueArray = SoundData->CommanderLTWaringSoundCueArray;
	if (LT_CommanderSoundCueArray.IsEmpty())
	{
		LT_CommanderSoundCueArray.Emplace(TempSoundCue);
	}
	GF_CommanderSoundCueArray = SoundData->CommanderGFWaringSoundCueArray;
	if (GF_CommanderSoundCueArray.IsEmpty())
	{
		GF_CommanderSoundCueArray.Emplace(TempSoundCue);
	}
	bIs_VG_FirstUsed = true;
	bIs_LT_FirstUsed = true;
	bIs_GF_FirstUsed = true;
	AnimInstance = Cast<UPPBossAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->SetCloseAlpha(0.f);
	
}

void APPCharacterBoss::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(bIsDead)
	{
		return;
	}
	
	GF_FX->SetWorldLocation(GetActorLocation());

	if (!bIsAttacking) // 보스전 너무 단조롭다면 패턴 여러개 사용하는 경우도 나오게끔 시간 체크만 하는게 나을지도
	{
		Core->SetAdditionalCollisionEnable(true);
		AnimInstance->SetIsIdle(true);
		ElapsedAttackDelay += DeltaSeconds;
		if (ElapsedAttackDelay >= AttackDelay)
		{
			EBossPattern RandPattern = GetRandomPattern();
			while (RandPattern == PreviousPattern)
			{
				RandPattern = GetRandomPattern();
			}

			switch (RandPattern)
			{
			case EBossPattern::VineGarden:
				GenerateTentaclesOnRandomLocation(VG_TentacleNum);
				break;
			case EBossPattern::LeafTempest:
				GenerateLeafTempestOnRandomLocation(LT_LeafNum);
				break;
			case EBossPattern::GreenFog:
				GenerateToxicFog();
				break;
			default:
				checkNoEntry();
			}

			PreviousPattern = RandPattern;
			// ElapsedAttackDelay = 0.f;
			// AttackDelay = FMath::RandRange(AttackDelayMin, AttackDelayMax);
		}
	}
	else
	{
		Core->SetAdditionalCollisionEnable(true);
		AnimInstance->SetIsIdle(false);
	}

	if (Health < BossData->MaxHP * 0.3f)
	{
		AnimInstance->SetIsIdle(false);
		OpenAndCloseNuclearContinuously();
	}
	else if (Health < BossData->MaxHP * 0.5f)
	{
		AnimInstance->SetIsIdle(false);
		OpenAndCloseNuclearByRandomDelay();
	}
}

EBossPattern APPCharacterBoss::GetRandomPattern() const
{
	return static_cast<EBossPattern>(FMath::RandRange(0, 2));
}

void APPCharacterBoss::ClearAllTimerOnLevelChange()
{
	GetWorldTimerManager().ClearTimer(GreenFogTimerHandle);
	GetWorldTimerManager().ClearTimer(LT_OnStageSilentTimer);
	GreenFogTimerHandle.Invalidate();
	LT_OnStageSilentTimer.Invalidate();
}

void APPCharacterBoss::GenerateTentaclesOnRandomLocation(uint32 InNum)
{
	bIsAttacking = true;
	uint32 GeneratedNum = 0;
	UGameplayStatics::PlaySound2D(this, VG_OmenSound);
	if (bIs_VG_FirstUsed)
	{
		bIs_VG_FirstUsed = false;
		UGameplayStatics::PlaySound2D(GetWorld()->GetFirstPlayerController(), VG_CommanderSoundCueArray[0]);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld()->GetFirstPlayerController(), VG_CommanderSoundCueArray[1]);
	}

	while (GeneratedNum < InNum)
	{
		FVector2d RandomPont = FMath::RandPointInCircle(VG_MaxDistance);
		const float Distance = FMath::RandRange(VG_MinDistance, VG_MaxDistance);
		RandomPont.Normalize();
		RandomPont *= Distance;

		FVector SpawnLocation = FVector(RandomPont.X, RandomPont.Y, 0.f) + GetActorLocation();
		SpawnLocation.Z = 0.f;

		FVector CollisionCheckLocation = SpawnLocation;
		CollisionCheckLocation.Z = 100.f;
		
		// 환경과 충돌이 있는지 검사
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			CollisionCheckLocation,
			CollisionCheckLocation,
			FQuat::Identity,
			ECC_WorldStatic,
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
		SpawnedActor->SetBoss(this);
		SpawnedActor->ShowWarningSign();

		++GeneratedNum;
	}
}

void APPCharacterBoss::GenerateLeafTempestOnRandomLocation(uint32 InNum)
{
	bIsAttacking = true;
	ALeaf::ResetLeafCount();
	uint32 GeneratedNum = 0;
	UGameplayStatics::PlaySound2D(this, LT_OmenSound);
	if (bIs_LT_FirstUsed)
	{
		bIs_LT_FirstUsed = false;
		UGameplayStatics::PlaySound2D(GetWorld()->GetFirstPlayerController(), LT_CommanderSoundCueArray[0]);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld()->GetFirstPlayerController(), LT_CommanderSoundCueArray[1]);
	}
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
			ECC_WorldStatic,
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
		LT_OnStage.Emplace(SpawnedActor);
		SpawnedActor->SetBoss(this);
		SpawnedActor->StartTracing();

		++GeneratedNum;
	}
}

void APPCharacterBoss::GenerateToxicFog()
{
	bIsAttacking = true;
	GF_ElapsedTime = 0.f;
	UGameplayStatics::PlaySound2D(this, GF_OmenSound);
	if (bIs_GF_FirstUsed)
	{
		bIs_GF_FirstUsed = false;
		UGameplayStatics::PlaySound2D(GetWorld()->GetFirstPlayerController(), GF_CommanderSoundCueArray[0]);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld()->GetFirstPlayerController(), GF_CommanderSoundCueArray[1]);
	}
	GetWorldTimerManager().SetTimer(GreenFogTimerHandle, this, &APPCharacterBoss::GenerateToxicFogDelegate, 1.f, true, 0.f);
}

void APPCharacterBoss::GenerateToxicFogDelegate()
{
	if (!bHasGFSpawned)
	{
		UGameplayStatics::PlaySound2D(this, GF_SpawnSound);
		GF_FX->Activate();
		bHasGFSpawned = true;
	}

	if (GF_ElapsedTime >= GF_Duration)
	{
		// FlushPersistentDebugLines(GetWorld());
		bHasGFSpawned = false;
		GetWorldTimerManager().ClearTimer(GreenFogTimerHandle);
		GF_FX->Deactivate();
		SetIsAttacking(false);
		FPPTimerHelper::InvalidateTimerHandle(GreenFogTimerHandle);
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
		ECC_CHECK_PLAYER,
		FCollisionShape::MakeSphere(GF_Radius),
		CollisionParams
	);

	// DrawDebugSphere(GetWorld(), GetActorLocation(), GF_Radius, 64, FColor::Green, false, 1.f);

	GF_ElapsedTime += FPPTimerHelper::GetActualDeltaTime(GreenFogTimerHandle);
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
}

void APPCharacterBoss::OpenAndCloseNuclearByRandomDelay()
{
	static float ElapsedTime = 0;
	static float RequiredDelay = FMath::RandRange(2.0f, 5.0f);

	ElapsedTime += GetWorld()->GetDeltaSeconds();
	if (ElapsedTime < RequiredDelay)
	{
		return;
	}
	constexpr float Pi = 3.141592;
	const float ElapsedTimeAfterDelay = ElapsedTime - RequiredDelay;
	const float Alpha = FMath::Sin(ElapsedTimeAfterDelay - Pi / 2) * 0.5f + 0.5f;
	AnimInstance->SetCloseAlpha(Alpha);
	Core->SetAdditionalCollisionEnable(Alpha < 0.5f);

	if (ElapsedTimeAfterDelay >= 2 * Pi)
	{
		AnimInstance->SetCloseAlpha(0.f);
		ElapsedTime = 0.f;
		RequiredDelay = FMath::RandRange(2.0f, 5.0f);
	}
}

void APPCharacterBoss::OpenAndCloseNuclearContinuously()
{
	static float ElapsedTime = 0;
	ElapsedTime += GetWorld()->GetDeltaSeconds();
	const float Alpha = FMath::Sin(ElapsedTime) * 0.5f + 0.5f;
	AnimInstance->SetCloseAlpha(Alpha);
	Core->SetAdditionalCollisionEnable(Alpha < 0.5f);
}

void APPCharacterBoss::IncreaseHealth(const float Value)
{
	Super::IncreaseHealth(Value);

	Health += Value;
}

void APPCharacterBoss::DecreaseHealth(const float Value)
{
	Super::DecreaseHealth(Value);
	Health -= Value;
	if (Health <= 0 && !bIsDead)
	{
		bIsDead = true;
		OpenTriggerDoorDelegate.Broadcast();
	}
}

void APPCharacterBoss::SetIsAttacking(const bool Value)
{
	bIsAttacking = Value;
	ElapsedAttackDelay = 0.f;
	AttackDelay = FMath::RandRange(AttackDelayMin, AttackDelayMax);
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

