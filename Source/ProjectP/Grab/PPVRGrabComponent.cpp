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
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);

	switch (GrabType)
	{
	case EVRGrabType::Free:
		{
			const bool Result = GetAttachParent()->AttachToComponent(Cast<UPrimitiveComponent>(InHand->GetMotionController()), AttachmentTransformRules);
			bHeld = Result;
			GrabbingHand = Result ? InHand : nullptr;
			break;
		}
	case EVRGrabType::ObjToHand:
		break;
	case EVRGrabType::HandToObj:
		break;
	default:
		checkNoEntry();
	}

	return bHeld;
}

void UPPVRGrabComponent::TryRelease()
{
	FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);

	if (GrabbingHand)
	{
		switch (GrabType)
		{
		case EVRGrabType::Free:
			GetAttachParent()->DetachFromComponent(DetachmentTransformRules);
			bHeld = false;
			SetPrimitiveCompPhysics(bShouldSimulateOnDrop);
			break;
		case EVRGrabType::ObjToHand:
			break;
		case EVRGrabType::HandToObj:
			break;
		default:
			checkNoEntry();
		}
		GrabbingHand = nullptr;
	}
}

void UPPVRGrabComponent::SetPrimitiveCompPhysics(const bool bInSimulate)
{
	Cast<UPrimitiveComponent>(GetAttachParent())->SetSimulatePhysics(bInSimulate);
}

void UPPVRGrabComponent::SetShouldSimulateOnDrop()
{
	bShouldSimulateOnDrop = Cast<UPrimitiveComponent>(GetAttachParent())->IsAnySimulatingPhysics();
}
