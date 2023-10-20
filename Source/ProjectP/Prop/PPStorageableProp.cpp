// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Prop/PPStorageableProp.h"

#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Util/PPCollisionChannels.h"

// Sets default values
APPStorageableProp::APPStorageableProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
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
void APPStorageableProp::BeginPlay()
{
	Super::BeginPlay();
	bIsGrabbed = false;

	GrabComponent->OnGrab.AddUObject(this, &APPStorageableProp::OnGrab);
	GrabComponent->OnRelease.AddUObject(this, &APPStorageableProp::OnRelease);
	
	UPPGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UPPGameInstance>();
	CommanderSound = GameInstance->GetSoundData()->CommanderAmpleSoundCue;
	GrabSound = GameInstance->GetSoundData()->AmpleGrabOnHandSoundCue;
}

// Called every frame
void APPStorageableProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsGrabbed)
	{
		FHitResult Result;
		FCollisionQueryParams Params(NAME_None, false, this);
		bool bPlayerHit = GetWorld()->SweepSingleByChannel(
			Result,
			GetActorLocation(),
			GetActorLocation(),
			FQuat::Identity,
			ECC_CHECK_PLAYER,
			FCollisionShape::MakeSphere(20.f),
			Params
		);
		if (bPlayerHit)
		{
			APPCharacterPlayer* Player = Cast<APPCharacterPlayer>(Result.GetActor());
			if (Player)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), GrabSound);
				Player->GetCommanderAudioComponent()->SetSound(CommanderSound);
				Player->GetCommanderAudioComponent()->Play();
				Destroy();
			}
		}
	}
}

void APPStorageableProp::OnGrab(APPVRHand* InHand)
{
	bIsGrabbed = true;
}

void APPStorageableProp::OnRelease(APPVRHand* InHand)
{
	bIsGrabbed = false;
}
