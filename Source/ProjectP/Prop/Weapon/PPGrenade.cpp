// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGrenade.h"

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
	FPPConstructorHelper::FindObjectAndInitialize<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/189-Grenade/SM_DummyGrenade.SM_DummyGrenade'"), [&](UStaticMesh* MeshRef)
	{
		Mesh->SetStaticMesh(MeshRef);
	}, EAssertionLevel::Check);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_GIMMICK);
	Mesh->SetEnableGravity(true);
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	GrabComponent = CreateDefaultSubobject<UPPVRGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(Mesh);
	GrabComponent->SetGrabType(EVRGrabType::ObjToHand);
	GrabComponent->SetShouldSimulateOnDrop(true);
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

	const APPVRPawn* Player = CastChecked<APPVRPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	CollisionParamsOnTick.AddIgnoredActor(this);
	CollisionParamsOnTick.AddIgnoredActor(Player);
	CollisionParamsOnTick.AddIgnoredActor(Player->GetLeftHand());
	CollisionParamsOnTick.AddIgnoredActor(Player->GetRightHand());
}

// Called every frame
void APPGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActivated)
	{
		return;
	}

	float Radius = 30.f;
	if (bIsWaitingForDelay)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Red, false, 0.f);
		return;
	}

	FHitResult Result;

	// TODO: Hand나 총 같은것도 추가...

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Green, false, 0.f);

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
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	if (!bHitResult)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("폭발: %s"), *Result.GetActor()->GetName());

	if (Result.GetActor() == Player->GetRightHand())
	{
		UE_LOG(LogTemp, Log, TEXT("같은 액터"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("같은 액터 아님"));
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
	bIsActivated = false;
	bIsWaitingForDelay = false;
	ElapsedActivatedTime = 0.f;
}

void APPGrenade::OnRelease(APPVRHand* InHand)
{
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
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	float Radius = 500.f; // TODO: 매직넘버 쓰면 안되긴 함 ㅎㅎ
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Red, false, 1.f);

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_PLAYER_ATTACK,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	if (!bHit)
	{
		Destroy();
		return;
	}

	for (auto Result : HitResults)
	{
		// TODO: 좀비 PPCharacterZombie 머지 되면 필터링 하기, 일단은 보스만 캐스팅해서 검사
		ICharacterStatusInterface* Enemy = Cast<ICharacterStatusInterface>(Result.GetActor());
		if (Enemy)
		{
			Enemy->DecreaseHealth(100.f);
		}
	}
	Destroy();
}
