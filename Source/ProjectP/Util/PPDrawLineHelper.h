#pragma once

#include "CoreMinimal.h"
#include "Components/LineBatchComponent.h"

class PROJECTP_API FPPDrawLineHelper 
{
public:
	static void DrawLine(const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, FColor const& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority, float Thickness)
	{
		bool bDepthIsForeground = (0 == SDPG_Foreground);

		ULineBatchComponent* LineBatcher = (InWorld ? (bDepthIsForeground ? InWorld->ForegroundLineBatcher : (( bPersistentLines || (LifeTime > 0.f) ) ? InWorld->PersistentLineBatcher : InWorld->LineBatcher)) : nullptr);

		if (LineBatcher)
		{
			LineBatcher->DrawLine(LineStart, LineEnd, Color, 0, Thickness, LifeTime);
		}
	}
};