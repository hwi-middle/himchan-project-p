// Fill out your copyright notice in the Description page of Project Settings.


#include "PPBossCore.h"

#include "PPCharacterBoss.h"
#include "ProjectP/Prop/Weapon/PPWeaponData.h"
#include "ProjectP/Util/PPConstructorHelper.h"

// Sets default values
APPBossCore::APPBossCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Tags.Add(TEXT("DestructibleObject"));
	PrimaryWeaponData = FPPConstructorHelper::FindAndGetObject<UPPWeaponData>(TEXT("/Script/ProjectP.PPWeaponData'/Game/DataAssets/Weapon/PrimaryWeaponData.PrimaryWeaponData'"), EAssertionLevel::Check);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoreMesh"));
	USkeletalMesh* MeshRef = FPPConstructorHelper::FindAndGetObject<USkeletalMesh>(TEXT("/Script/Engine.SkeletalMesh'/Game/Project-P/Meshes/SkeletalMesh/Boss/BossCore/heart_animation_2__1_.heart_animation_2__1_'"));
	Mesh->SetSkeletalMesh(MeshRef);
	const float ScaleFactor = 2.198526;
	Mesh->SetWorldScale3D(FVector(ScaleFactor));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Mesh->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));

	AdditionalCollision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AdditionalCollisionBox"));
	AdditionalCollision->SetStaticMesh(FPPConstructorHelper::FindAndGetObject<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"), EAssertionLevel::Check));
	AdditionalCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AdditionalCollision->SetCollisionProfileName(TEXT("IgnoreOnlyPawn"));
	AdditionalCollision->SetVisibility(false);
	AdditionalCollision->SetupAttachment(Mesh);
	AdditionalCollision->SetRelativeLocation(FVector(0.0f, 40.0f, 170.0f));
	AdditionalCollision->SetRelativeScale3D(FVector(0.65f,0.8f * 3,0.6f));
	
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
	Boss->DecreaseHealth(Value * PrimaryWeaponData->HeadShotDamageScaleFactor);
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

