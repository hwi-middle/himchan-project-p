// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectP/Game/PPVRGameMode.h"
#include "ProjectP/Util/PPConstructorHelper.h"


APPVRGameMode::APPVRGameMode()
{
	DefaultPawnClass = FPPConstructorHelper::FindAndGetClass<APawn>(TEXT("/Script/CoreUObject.Class'/Script/ProjectP.PPCharacterPlayer'"));
	PlayerControllerClass = FPPConstructorHelper::FindAndGetClass<APlayerController>(TEXT("/Script/CoreUObject.Class'/Script/ProjectP.PPPlayerController'"));
}

