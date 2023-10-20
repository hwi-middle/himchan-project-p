// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGrenade.h"

#include "GrenadeData.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "ProjectP/Grab/PPVRGrabComponent.h"
#include "ProjectP/Player/PPVRPawn.h"
#include "ProjectP/Util/PPCollisionChannels.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPGrenade::APPGrenade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrenadeMesh"));
	FPPConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/Project-P/Meshes/Granade/Mesh/SM_Grenade.SM_Grenade'"), [&](UStaticMesh* MeshRef)
	{
		Mesh->SetStaticMesh(MeshRef);
	}, EAssertionLevel::Check);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_GIMMICK);
	Mesh->SetEnableGravity(true);
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	GrenadeData = FPPConstructorHelper::FindAndGetObject<UGrenadeData>(TEXT("/Script/ProjectP.GrenadeData'/Game/DataAssets/Weapon/GrenadeData.GrenadeData'"));

	GrabComponent = CreateDefaultSubobject<UPPVRGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(Mesh);
	GrabComponent->SetGrabType(EVRGrabType::ObjToHand);
	GrabComponent->SetShouldSimulateOnDrop(true);
	//GrabComponent->SetIsWeapon(true);
	UE_LOG(LogTemp, Log, TEXT("Grenade"));
}

// Called when the game starts or when spawned
void APPGrenade::BeginPlay()
{
	Super::BeginPlay();
	bIsActivated = false;
	bIsWaitingForDelay = false;
	ElapsedActivatedTime = 0.f;
	ExplodeDelay = 3.0f;

	GrabComponent->OnGrab.AddUObject(this, &APPGrenade::OnGrab);
	GrabComponent->OnRelease.AddUObject(this, &APPGrenade::OnRelease);

	CollisionParamsOnTick.AddIgnoredActor(this);
	if (const APPVRPawn* Player = Cast<APPVRPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); Player != nullptr)
	{
		CollisionParamsOnTick.AddIgnoredActor(Player);
		CollisionParamsOnTick.AddIgnoredActor(Player->GetLeftHand());
		CollisionParamsOnTick.AddIgnoredActor(Player->GetRightHand());
	}

	ExplodeDelay = GrenadeData->ExplodeDelay;
	ExplodeType = GrenadeData->ExplodeType;
	ActivateRadius = GrenadeData->ActivateRadius * 100;
	ExplodeRadius = GrenadeData->ExplodeRadius * 100;
	ExplodeDamage = GrenadeData->ExplodeDamage;
}

// Called every frame
void APPGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActivated)
	{
		return;
	}

	if (bIsWaitingForDelay)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), ActivateRadius, 16, FColor::Red, false, 0.f);
		return;
	}

	FHitResult Result;

	// TODO: Hand나 총 같은것도 추가...

	DrawDebugSphere(GetWorld(), GetActorLocation(), ActivateRadius, 16, FColor::Green, false, 0.f);

	FCollisionQueryParams CollisionParams;
	const APPVRPawn* Player = CastChecked<APPVRPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(Player);
	CollisionParams.AddIgnoredActor(Player->GetLeftHand());
	CollisionParams.AddIgnoredActor(Player->GetRightHand());

	bool bHitResult = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(ActivateRadius),
		CollisionParams
	);

	if (!bHitResult)
	{
		return;
	}

	bIsActivated = true;

	if (ExplodeType == EGrenadeExplodeType::OnImpact)
	{
		Explode();
	}
	else if (ExplodeType == EGrenadeExplodeType::OnImpactWithDelay)
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &APPGrenade::WaitForDelayAndExplode);
	}
}

void APPGrenade::OnGrab(APPVRHand* InHand)
{
	UE_LOG(LogTemp, Log, TEXT("OnGrab"));
	bIsActivated = false;
	bIsWaitingForDelay = false;
	ElapsedActivatedTime = 0.f;
}

void APPGrenade::OnRelease(APPVRHand* InHand)
{
	UE_LOG(LogTemp, Log, TEXT("수류탄 Release"));
	bIsActivated = true;
	if (ExplodeType == EGrenadeExplodeType::OnReleaseWithDelay)
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &APPGrenade::WaitForDelayAndExplode);
	}
}

void APPGrenade::WaitForDelayAndExplode()
{
	if (!bIsActivated)
	{
		return;
	}

	bIsWaitingForDelay = true;
	const float DeltaTime = GWorld->DeltaTimeSeconds;
	ElapsedActivatedTime += DeltaTime;

	if (ElapsedActivatedTime < ExplodeDelay)
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &APPGrenade::WaitForDelayAndExplode);
		return;
	}

	Explode();
}

void APPGrenade::Explode()
{
	UE_LOG(LogTemp, Log, TEXT("폭발"));
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplodeRadius, 16, FColor::Red, false, 1.f);

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_PLAYER_ATTACK,
		FCollisionShape::MakeSphere(ExplodeRadius),
		CollisionParams
	);

	if (!bHit)
	{
		Destroy();
		return;
	}

	for (auto Result : HitResults)
	{
		ICharacterStatusInterface* Enemy = Cast<ICharacterStatusInterface>(Result.GetActor());
		if (Enemy)
		{
			Enemy->DecreaseHealth(ExplodeDamage);
		}
	}
	Destroy();
}
