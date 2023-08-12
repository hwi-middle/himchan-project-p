// Fill out your copyright notice in the Description page of Project Settings.


#include "PPWarningZoneCylinder.h"

#include "ProjectP/Util/PPConstructorHelper.h"

APPWarningZoneCylinder::APPWarningZoneCylinder()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WarningCylinderMesh"));
	UStaticMesh* MeshObj = FPPConstructorHelper::FindAndGetObject<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/BossPatternTest/WarningCylinder.WarningCylinder'"), EAssertionLevel::Check);
	Mesh->SetStaticMesh(MeshObj);
	Mesh->SetRelativeScale3D(FVector(1.f,1.f,4.f));
}

void APPWarningZoneCylinder::BeginPlay()
{
	Super::BeginPlay();

	
}
