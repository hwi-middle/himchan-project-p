// Fill out your copyright notice in the Description page of Project Settings.


#include "PPVRGrabComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectP/Enumeration/PPVRGrabType.h"
#include "ProjectP/Game/PPGameInstance.h"
#include "ProjectP/Player/PPVRHand.h"

// Sets default values for this component's properties
UPPVRGrabComponent::UPPVRGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsWeapon = false;
	// ...
}


// Called when the game starts
void UPPVRGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPPVRGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPPVRGrabComponent::TryGrab(APPVRHand* InHand)
{
	switch (GrabType)
	{
	case EVRGrabType::Free:
		TryAttachComponentToHand(InHand);
		break;
	case EVRGrabType::ObjToHand:
		{
			TryAttachComponentToHand(InHand);

			// 회전 보정
			GetAttachParent()->SetRelativeRotation(GetRelativeRotation().GetInverse(), false, nullptr, ETeleportType::TeleportPhysics);
			const FRotator CurrentRotation = GetAttachParent()->GetRelativeRotation();
			GetAttachParent()->SetRelativeRotation(FRotator(CurrentRotation.Pitch - 90.f, CurrentRotation.Yaw, CurrentRotation.Roll), false, nullptr, ETeleportType::TeleportPhysics);

			// 위치 보정
			const FVector ComponentToParentDir = GetAttachParent()->GetComponentLocation() - GetComponentLocation();
			const FVector NewLocation = InHand->GetMotionController()->GetComponentLocation() + ComponentToParentDir;
			GetAttachParent()->SetWorldLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			break;
		}
	case EVRGrabType::HandToObj:
		TryAttachHandToComponent(InHand);
		break;
	default:
		checkNoEntry();
	}
	
	if (bHeld)
	{
		OnGrab.Broadcast(GrabbingHand);
	}

	// 물체를 잡는 동안은 물리 적용 해제
	SetPrimitiveCompPhysics(false);
	return bHeld;
}

void UPPVRGrabComponent::TryRelease()
{
	if (!GrabbingHand)
	{
		return;
	}

	OnRelease.Broadcast(GrabbingHand);

	if (GrabType == EVRGrabType::HandToObj)
	{
		GrabbingHand->ResetHandMesh();
	}
	else
	{
		GetAttachParent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}

	bHeld = false;
	SetPrimitiveCompPhysics(bShouldSimulateOnDrop);
	GrabbingHand = nullptr;
}

void UPPVRGrabComponent::SetPrimitiveCompPhysics(const bool bInSimulate)
{
	Cast<UPrimitiveComponent>(GetAttachParent())->SetSimulatePhysics(bInSimulate);
}

// void UPPVRGrabComponent::SetShouldSimulateOnDrop()
// {
// 	bShouldSimulateOnDrop = Cast<UPrimitiveComponent>(GetAttachParent())->IsAnySimulatingPhysics();
// }

void UPPVRGrabComponent::TryAttachComponentToHand(APPVRHand* InHand)
{
	bHeld = GetAttachParent()->AttachToComponent(InHand->GetMotionController(), FAttachmentTransformRules::KeepWorldTransform);
	GrabbingHand = bHeld ? InHand : nullptr;
}

void UPPVRGrabComponent::TryAttachHandToComponent(APPVRHand* InHand)
{
	bHeld = InHand->GetHandMesh()->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	GrabbingHand = bHeld ? InHand : nullptr;
	InHand->GetHandMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 90.f));
}
