// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterZombie.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/AI/Zombie/PPZombieAIController.h"
#include "ProjectP/Constant/PPMontageSectionName.h"
#include "ProjectP/Constant/PPSkeletalMeshSocketName.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"

APPCharacterZombie::APPCharacterZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("DestructibleObject"));
	AIControllerClass = APPZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	ZombieData = FPPConstructorHelper::FindAndGetObject<UPPZombieData>(TEXT("/Script/ProjectP.PPZombieData'/Game/186-ZombieAI/ZombieData.ZombieData'"), EAssertionLevel::Check);
	GetMesh()->SetSkeletalMesh(ZombieData->ZombieMesh);
	GetMesh()->SetAnimInstanceClass(FPPConstructorHelper::FindAndGetClass<UPPZombieAnimInstance>(TEXT("/Script/Engine.AnimBlueprint'/Game/186-ZombieAI/ABP_Zombie.ABP_Zombie_C'"), EAssertionLevel::Check));

	HitNiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HitVFX"));
	UNiagaraSystem* HitNiagaraSystem = FPPConstructorHelper::FindAndGetObject<UNiagaraSystem>(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/BloodFX/Fx/NS_BloodSpalatter_001.NS_BloodSpalatter_001'"), EAssertionLevel::Check);
	HitNiagaraEffect->SetAsset(HitNiagaraSystem);
	HitNiagaraEffect->SetAutoActivate(false);
	HitNiagaraEffect->SetActive(false);
	// GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// GetMesh()->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
}

float APPCharacterZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DecreaseHealth(DamageAmount);
	APPZombieAIController* ZombieAIController = Cast<APPZombieAIController>(GetController());
	if(ZombieAIController)
	{
		TArray<AActor*> Target;
		Target.Emplace(DamageCauser);
		ZombieAIController->SetTarget(Target);
	}
	return 0;
}

void APPCharacterZombie::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionProfileName(CP_ENEMY);
	HitNiagaraEffect->SetActive(false);
	
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Health = ZombieData->Health;
	AttackDamage = ZombieData->AttackDamage;
	AttackRange = ZombieData->AttackRange;
	AttackHitCheckBox = ZombieData->AttackHitCheckBox;
	AutoDestroyTime = ZombieData->AutoDestroyTime;

	PatrolRadius = ZombieData->PatrolRadius;
	DetectRadius = ZombieData->DetectRadius;
	MissingTargetRadius = ZombieData->MissingTargetRadius;
	ResearchSpeed = ZombieData->ResearchMoveSpeed;
	TrackingSpeed = ZombieData->TrackingMoveSpeed;
	DetectDegrees = ZombieData->DetectDegrees;
	ZombieAnimMontage = ZombieData->ZombieAnimMontage;
	
	CurrentState = ECharacterState::Idle;
	GetCharacterMovement()->MaxWalkSpeed = ZombieData->ResearchMoveSpeed;
	ZombieAnimInstance = Cast<UPPZombieAnimInstance>(GetMesh()->GetAnimInstance());
	if(ZombieAnimInstance)
	{
		// 애님 노티파이 연결
		ZombieAnimInstance->HitCheckStartDelegate.AddUObject(this, &APPCharacterZombie::AttackHitCheckStart);
		ZombieAnimInstance->HitCheckEndDelegate.AddUObject(this, &APPCharacterZombie::AttackHitCheckEnd);
		ZombieAnimInstance->AttackAnimEndDelegate.AddUObject(this, &APPCharacterZombie::AttackFinishedNotify);
		ZombieAnimInstance->DeadAnimEndDelegate.AddUObject(this, &APPCharacterZombie::SetDeadLoop);
	}
}

void APPCharacterZombie::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//TODO: 시간이 된다면 다른 클래스들도 BeginDestroy()에 타이머 해제 추가하기
void APPCharacterZombie::BeginDestroy()
{
	Super::BeginDestroy();
	DeadTimerHandle.Invalidate();
	AttackHitCheckTimerHandle.Invalidate();
}

void APPCharacterZombie::SetDeadLoop()
{
	GetMesh()->GetAnimInstance()->Montage_Play(ZombieAnimMontage);
	GetMesh()->GetAnimInstance()->Montage_JumpToSection(AM_SECTION_DEAD_LOOP, ZombieAnimMontage);
	GetMesh()->GetAnimInstance()->Montage_Pause(ZombieAnimMontage);
	GetWorldTimerManager().SetTimer(DeadTimerHandle, this, &APPCharacterZombie::DestroyThis, AutoDestroyTime, false);
}

void APPCharacterZombie::DestroyThis()
{
	Destroy();
}

void APPCharacterZombie::TakeDamageEffect(FVector HitLocation)
{
	HitNiagaraEffect->SetRelativeLocation(HitLocation);
	HitNiagaraEffect->SetRelativeRotation(HitLocation.Rotation());
	HitNiagaraEffect->SetActive(true);
}

void APPCharacterZombie::SetAIPatternDelegate(const FAICharacterPatternFinished& FinishedDelegate)
{
	PatternFinishedDelegate = FinishedDelegate;
}

void APPCharacterZombie::PlayPatternAnimMontage()
{
	GetMesh()->GetAnimInstance()->Montage_Play(ZombieAnimMontage);
	switch (CurrentState)
	{
	case ECharacterState::Attack:
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(AM_SECTION_ATTACK, ZombieAnimMontage);
		break;
	case ECharacterState::Dead:
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(AM_SECTION_DEAD, ZombieAnimMontage);
		ZombieAnimInstance->StopAttackBlend();
		break;
	default:
		// Idle Or Tracking?
		break;
	}
}

void APPCharacterZombie::IncreaseHealth(const float Value)
{
	Super::IncreaseHealth(Value);
	Health += Value;
}
void APPCharacterZombie::DecreaseHealth(const float Value)
{
	Super::DecreaseHealth(Value);
	if(CurrentState == ECharacterState::Dead)
	{
		return;
	}
	Health -= Value;
	if(Health <= 0)
	{
		if(GetController())
		{
			GetController()->Destroy();
		}
		GetCapsuleComponent()->SetCapsuleSize(1.f, 1.f);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CurrentState = ECharacterState::Dead;
		PlayPatternAnimMontage();
	}
}

void APPCharacterZombie::CheckAttackHitResult()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
		
	bool bResult = GetWorld()->SweepSingleByChannel(
	HitResult,
	GetMesh()->GetSocketLocation(ZOMBIE_FRONT),
	GetMesh()->GetSocketLocation(ZOMBIE_FRONT),
	FQuat::Identity,
	ECC_ENEMY_ATTACK,
	FCollisionShape::MakeBox(AttackHitCheckBox),
	Params);
	DrawDebugBox(GetWorld(), GetMesh()->GetSocketLocation(ZOMBIE_FRONT), AttackHitCheckBox, FColor::Blue, false, 1.0f);
	if(bResult && !bIsDamageCaused)
	{
		APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(HitResult.GetActor());
		// ACharacter* TestPlayer = Cast<ACharacter>(HitResult.GetActor());
		if(Player)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("공격 체크")));
			bIsDamageCaused = true;
			FDamageEvent DamageEvent;
			Player->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}
}

void APPCharacterZombie::AttackHitCheckStart()
{
	GetWorldTimerManager().SetTimer(AttackHitCheckTimerHandle, this, &APPCharacterZombie::CheckAttackHitResult, 0.01f, true);
}

void APPCharacterZombie::AttackHitCheckEnd()
{
	if(GetWorldTimerManager().IsTimerActive(AttackHitCheckTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(AttackHitCheckTimerHandle);
	}
}

void APPCharacterZombie::AttackFinishedNotify()
{
	bIsDamageCaused = false;
	PatternFinishedDelegate.Broadcast();
}
