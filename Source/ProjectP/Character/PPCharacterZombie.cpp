// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterZombie.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"

#include "ProjectP/Character/PPCharacterPlayer.h"
#include "ProjectP/Animation/PPZombieAnimInstance.h"
#include "ProjectP/AI/Zombie/PPZombieAIController.h"
#include "ProjectP/Constant/PPMontageSectionName.h"
#include "ProjectP/Constant/PPSkeletalMeshSocketName.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"

APPCharacterZombie::APPCharacterZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = APPZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	ZombieData = FPPConstructorHelper::FindAndGetObject<UPPZombieData>(TEXT("/Script/ProjectP.PPZombieData'/Game/186-ZombieAI/ZombieData.ZombieData'"), EAssertionLevel::Check);
	GetMesh()->SetSkeletalMesh(ZombieData->ZombieMesh);
	GetMesh()->SetAnimInstanceClass(FPPConstructorHelper::FindAndGetClass<UPPZombieAnimInstance>(TEXT("/Script/Engine.AnimBlueprint'/Game/186-ZombieAI/ABP_Zombie.ABP_Zombie_C'"), EAssertionLevel::Check));
	
	PatrolRadius = ZombieData->PatrolRadius;
	DetectRadius = ZombieData->DetectRadius;
	MissingTargetRadius = ZombieData->MissingTargetRadius;
	ResearchSpeed = ZombieData->ResearchMoveSpeed;
	TrackingSpeed = ZombieData->ResearchMoveSpeed;
	DetectDegrees = ZombieData->DetectDegrees;
	ZombieAnimMontage = ZombieData->ZombieAnimMontage;
}

float APPCharacterZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                     AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void APPCharacterZombie::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Health = ZombieData->Health;
	CurrentState = ECharacterState::Idle;
	GetCharacterMovement()->MaxWalkSpeed = ZombieData->ResearchMoveSpeed;
	UPPZombieAnimInstance* ZombieAnimInstance = Cast<UPPZombieAnimInstance>(GetMesh()->GetAnimInstance());
	if(ZombieAnimInstance)
	{
		// 애님 노티파이 연결
		ZombieAnimInstance->HitCheckStartDelegate.AddUObject(this, &APPCharacterZombie::AttackHitCheckStart);
		ZombieAnimInstance->HitCheckEndDelegate.AddUObject(this, &APPCharacterZombie::AttackHitCheckEnd);
	}
}

void APPCharacterZombie::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APPCharacterZombie::BeginDestroy()
{
	Super::BeginDestroy();
}

void APPCharacterZombie::SetDead(UAnimMontage* Montage, bool IsInterrupted)
{
	GetMesh()->GetAnimInstance()->Montage_JumpToSection(AM_SECTION_DEAD_LOOP, ZombieAnimMontage);
	GetMesh()->GetAnimInstance()->Montage_Pause();
}

void APPCharacterZombie::SetAIPatternDelegate(FAICharacterPatternFinished FinishedDelegate)
{
	PatternFinishedDelegate = FinishedDelegate;
}

void APPCharacterZombie::PlayPatternAnimMontage(ECharacterState State)
{
	PlayAnimMontage(ZombieAnimMontage);
	switch (State)
	{
	case ECharacterState::Attack:
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(AM_SECTION_ATTACK, ZombieAnimMontage);
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &APPCharacterZombie::AttackFinishedNotify);
		break;
	case ECharacterState::Dead:
		GetMesh()->GetAnimInstance()->OnMontageEnded.Clear();
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(AM_SECTION_DEAD, ZombieAnimMontage);
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &APPCharacterZombie::SetDead);
		break;
	default:
		checkNoEntry();
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
	ECC_CHECK_PAWN,
	FCollisionShape::MakeBox(AttackHitCheckBox),
	Params);
			
	if(bResult && !bIsDamageCaused)
	{
		APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(HitResult.GetActor());
		if(Player)
		{
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

void APPCharacterZombie::AttackFinishedNotify(UAnimMontage* Montage, bool IsInterrupted)
{
	bIsDamageCaused = false;
	PatternFinishedDelegate.Broadcast();
}
