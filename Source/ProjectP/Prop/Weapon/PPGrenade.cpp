// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGrenade.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Character/PPCharacterBoss.h"
#include "ProjectP/Grab/PPVRGrabComponent.h"
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
}

// Called when the game starts or when spawned
void APPGrenade::BeginPlay()
{
	Super::BeginPlay();
	bIsActivated = false;
	ElapsedActivatedTime = 0.f;
	ExplodeDelay = 2.0f;
}

// Called every frame
void APPGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	float Radius = 55.f;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	// TODO: Hand나 총 같은것도 추가...

	if (bIsActivated)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Red, false, 0.f);
		return;
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Green, false, 0.f);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	if (bHit)
	{
		bIsActivated = true;
		GetWorldTimerManager().SetTimerForNextTick(this, &APPGrenade::Activate);
	}
}

void APPGrenade::Activate()
{
	const float DeltaTime = GWorld->DeltaTimeSeconds;
	ElapsedActivatedTime += DeltaTime;

	if (ElapsedActivatedTime < ExplodeDelay)
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &APPGrenade::Activate);
		return;
	}

	FHitResult Result;
	FCollisionQueryParams CollisionParams;
	float Radius = 500.f; // TODO: 매직넘버 쓰면 안되긴 함 ㅎㅎ
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, FColor::Red, false, 1.f);

	bool bHit = GetWorld()->SweepSingleByChannel(
		Result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(Radius),
		CollisionParams
	);

	if (!bHit)
	{
		Destroy();
		return;
	}

	// TODO: 좀비 PPCharacterZombie 머지 되면 필터링 하기, 일단은 보스만 캐스팅해서 검사
	APPCharacterBoss* Enemy = Cast<APPCharacterBoss>(Result.GetActor());
	if (Enemy)
	{
		FDamageEvent DamageEvent;
		Enemy->TakeDamage(10.f, DamageEvent, nullptr, this);
	}

	Destroy();
}
