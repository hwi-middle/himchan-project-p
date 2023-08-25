// Fill out your copyright notice in the Description page of Project Settings.


#include "PPBossCore.h"

#include "PPCharacterBoss.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPBossCore::APPBossCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Tags.Add(TEXT("DestructibleObject"));

	AdditionalCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AdditionalCollisionBox"));
	//AdditionalCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AdditionalCollision->SetCapsuleHalfHeight(70.0f);
	AdditionalCollision->SetCapsuleRadius(50.0f);
	//AdditionalCollision->SetRelativeLocation();
	RootComponent = AdditionalCollision;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoreMesh"));
	USkeletalMesh* MeshRef = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Project-P/Meshes/SkeletalMesh/Boss/BossCore/heart_animation_2__1_.heart_animation_2__1_'"));
	Mesh->SetSkeletalMesh(MeshRef);
	const float ScaleFactor = 2.198526;
	Mesh->SetWorldScale3D(FVector(ScaleFactor));
	//RootComponent = Mesh;
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));

	UAnimSequence* AnimRef = FPPConstructorHelper::FindAndGetObject<UAnimSequence>(TEXT("/Script/Engine.AnimSequence'/Game/Project-P/Meshes/SkeletalMesh/Boss/BossCore/heart_animation_2__1__Anim.heart_animation_2__1__Anim'"));
	Anim = AnimRef;
}

// Called when the game starts or when spawned
void APPBossCore::BeginPlay()
{
	Super::BeginPlay();
	Mesh->PlayAnimation(Anim, true);
}

// Called every frame
void APPBossCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APPBossCore::IncreaseHealth(const float Value)
{
	Health += Value;
}

void APPBossCore::DecreaseHealth(const float Value)
{
	Boss->DecreaseHealth(Value);
}

void APPBossCore::SetAdditionalCollisionEnable(const bool Value)
{
	if(Value)
	{
		AdditionalCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		AdditionalCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

