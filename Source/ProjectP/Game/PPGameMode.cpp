// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGameMode.h"

APPGameMode::APPGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/ProjectP.PPCharacterPlayer"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ProjectP.PPPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
