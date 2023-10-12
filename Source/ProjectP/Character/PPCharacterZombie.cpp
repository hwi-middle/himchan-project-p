// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Character/PPCharacterZombie.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectP/AI/Zombie/PPZombieAIController.h"
#include "ProjectP/Util/PPConstructorHelper.h"

APPCharacterZombie::APPCharacterZombie()
{
	AIControllerClass = APPZombieAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	ZombieData = FPPConstructorHelper::FindAndGetObject<UPPZombieData>(TEXT("/Script/ProjectP.PPZombieData'/Game/186-ZombieAI/ZombieData.ZombieData'"), EAssertionLevel::Check);
	GetMesh()->SetSkeletalMesh(ZombieData->ZombieMesh);
	PatrolRadius = ZombieData->PatrolRadius;
	DetectRadius = ZombieData->DetectRadius;
	MissingTargetRadius = ZombieData->MissingTargetRadius;
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
	GetCharacterMovement()->MaxWalkSpeed = ZombieData->MoveSpeed;
}

void APPCharacterZombie::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APPCharacterZombie::BeginDestroy()
{
	Super::BeginDestroy();
}

void APPCharacterZombie::Attack()
{
	
}

void APPCharacterZombie::SetDead()
{
	
}

void APPCharacterZombie::SetAIPatternDelegate(FAICharacterPatternFinished FinishedDelegate)
{
	PatternFinishedDelegate = FinishedDelegate;
}

void APPCharacterZombie::PlayPatternAnimMontage()
{
	// 대충 공격 애님 몽타주 실행하는 곳
	PlayAnimMontage(ZombieAnimMontage);
	// GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &APPCharacterZombie::AttackFinishedNotify);
	// 테스트용
	// GetMesh()->GetAnimInstance()->OnMontageEnded.Broadcast(ZombieAnimMontage, false);
}

void APPCharacterZombie::CheckAttackResult()
{
	
}

void APPCharacterZombie::AttackFinishedNotify(UAnimMontage* Montage, bool IsInterrupted)
{
	PatternFinishedDelegate.Broadcast();
}
