// Fill out your copyright notice in the Description page of Project Settings.


#include "PPVRGrabComponent.h"
#include "ProjectP/Enumeration/PPVRGrabType.h"
#include "ProjectP/Player/PPVRHand.h"

// Sets default values for this component's properties
UPPVRGrabComponent::UPPVRGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
		{
			const bool Result = GetAttachParent()->AttachToComponent(Cast<UPrimitiveComponent>(InHand->GetMotionController()), FAttachmentTransformRules::KeepWorldTransform);
			bHeld = Result;
			GrabbingHand = Result ? InHand : nullptr;
			break;
		}
	case EVRGrabType::ObjToHand:
		{
			const bool Result = GetAttachParent()->AttachToComponent(Cast<UPrimitiveComponent>(InHand->GetMotionController()), FAttachmentTransformRules::KeepWorldTransform);
			bHeld = Result;
			GrabbingHand = Result ? InHand : nullptr;

			// 회전 보정
			GetAttachParent()->SetRelativeRotation(GetRelativeRotation().GetInverse(), false, nullptr, ETeleportType::TeleportPhysics);

			// 위치 보정
			FVector ComponentToParentDir = GetAttachParent()->GetComponentLocation() - GetComponentLocation();
			FVector NewLocation = GetComponentLocation() + ComponentToParentDir;
			GetAttachParent()->SetWorldLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			break;
		}
	case EVRGrabType::HandToObj:
		{
			const bool Result = InHand->GetHandMesh()->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			bHeld = Result;
			GrabbingHand = Result ? InHand : nullptr;
			InHand->GetHandMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 90.f));
			break;
		}
	default:
		checkNoEntry();
	}

	SetPrimitiveCompPhysics(false);
	return bHeld;
}

void UPPVRGrabComponent::TryRelease()
{
	if (!GrabbingHand)
	{
		return;
	}

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

void UPPVRGrabComponent::SetShouldSimulateOnDrop()
{
	bShouldSimulateOnDrop = Cast<UPrimitiveComponent>(GetAttachParent())->IsAnySimulatingPhysics();
}
