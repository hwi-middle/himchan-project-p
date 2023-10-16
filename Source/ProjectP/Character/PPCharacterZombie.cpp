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
}

float APPCharacterZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageAmount;
	if(Health <= 0)
	{
		GetController()->Destroy();
		CurrentState = ECharacterState::Dead;
		PlayPatternAnimMontage();
	}
	return 0;
}

void APPCharacterZombie::BeginPlay()
{
	Super::BeginPlay();
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
	UPPZombieAnimInstance* ZombieAnimInstance = Cast<UPPZombieAnimInstance>(GetMesh()->GetAnimInstance());
	if(ZombieAnimInstance)
	{
		// 애님 노티파이 연결
		ZombieAnimInstance->HitCheckStartDelegate.AddUObject(this, &APPCharacterZombie::AttackHitCheckStart);
		ZombieAnimInstance->HitCheckEndDelegate.AddUObject(this, &APPCharacterZombie::AttackHitCheckEnd);
		ZombieAnimInstance->AttackAnimEndDelegate.AddUObject(this, &APPCharacterZombie::AttackFinishedNotify);
		ZombieAnimInstance->DeadAnimEndDelegate.AddUObject(this, &APPCharacterZombie::SetDead);
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
	if(DeadTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DeadTimerHandle);
		DeadTimerHandle.Invalidate();
	}

	if(AttackHitCheckTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(AttackHitCheckTimerHandle);
		AttackHitCheckTimerHandle.Invalidate();
	}
	Destroy();
}

void APPCharacterZombie::SetDead()
{
	GetMesh()->GetAnimInstance()->Montage_JumpToSection(AM_SECTION_DEAD_LOOP, ZombieAnimMontage);
	GetMesh()->GetAnimInstance()->Montage_Pause();
	GetWorldTimerManager().SetTimer(DeadTimerHandle, this, &APPCharacterZombie::BeginDestroy, AutoDestroyTime, false);
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
		break;
	default:
		// Idle Or Tracking?
		break;
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
	ECC_Pawn,
	FCollisionShape::MakeBox(AttackHitCheckBox),
	Params);
	DrawDebugBox(GetWorld(), GetMesh()->GetSocketLocation(ZOMBIE_FRONT), AttackHitCheckBox, FColor::Blue, false, 1.0f);
	if(bResult && !bIsDamageCaused)
	{
		// APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(HitResult.GetActor());
		ACharacter* Player = Cast<ACharacter>(HitResult.GetActor());
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
