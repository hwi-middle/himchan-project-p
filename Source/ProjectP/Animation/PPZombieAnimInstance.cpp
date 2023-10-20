// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Animation/PPZombieAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "ProjectP/Util/PPConstructorHelper.h"
#include "ProjectP/Character/PPZombieData.h"
#include "ProjectP/Game/PPGameInstance.h"

UPPZombieAnimInstance::UPPZombieAnimInstance()
{
	OwnerData = FPPConstructorHelper::FindAndGetObject<UPPZombieData>(TEXT("/Script/ProjectP.PPZombieData'/Game/186-ZombieAI/ZombieData.ZombieData'"), EAssertionLevel::Check);
}

void UPPZombieAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwnerCharacter = Cast<ACharacter>(GetOwningActor());
	if(OwnerCharacter)
	{
		MovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UPPZombieAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Velocity = FVector::ZeroVector;
	MoveSpeed = 0.f;
	TrackBlendWithAttackValue = 0.f;
	ResearchThreshold = OwnerData->ResearchThreshold;
	TrackingThreshold = OwnerData->TrackingThreshold;
	TrackToAttackBlendSpeed = OwnerData->TrackToAttackBlendSpeed;
	bIsIdle = true;
	bIsTrack = false;
}

void UPPZombieAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(MovementComponent)
	{
		Velocity = MovementComponent->Velocity;
		MoveSpeed = Velocity.Size2D();
		if(!bIsTrack)
		{
			bIsIdle = MoveSpeed < ResearchThreshold;
		}
		bIsTrack = MoveSpeed > TrackingThreshold;
	}
}

void UPPZombieAnimInstance::AnimNotify_AttackHitCheckStart()
{
	HitCheckStartDelegate.Broadcast();
	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	UGameplayStatics::PlaySound2D(GetWorld(), GameInstance->GetSoundData()->ZombieAttackSoundCue);
	GetWorld()->GetTimerManager().SetTimer(AnimBlendTimerHandle, this, &UPPZombieAnimInstance::AnimBlendSequence, 0.01f, true);
}

void UPPZombieAnimInstance::AnimNotify_AttackHitCheckEnd()
{
	HitCheckEndDelegate.Broadcast();
	if(GetWorld()->GetTimerManager().IsTimerActive(AnimBlendTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(AnimBlendTimerHandle);
	}
	TrackBlendWithAttackValue = 0.f;
}

void UPPZombieAnimInstance::AnimNotify_AttackAnimEnd()
{
	AttackAnimEndDelegate.Broadcast();
}

void UPPZombieAnimInstance::AnimNotify_EnterDeadLoop()
{
	DeadAnimEndDelegate.Broadcast();
}

void UPPZombieAnimInstance::AnimBlendSequence()
{
	TrackBlendWithAttackValue += TrackToAttackBlendSpeed;
}
