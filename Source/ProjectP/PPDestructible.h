// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interface/CharacterStatusInterface.h"
#include "PPDestructible.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTP_API UPPDestructible : public USceneComponent, public ICharacterStatusInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPPDestructible();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	float Health;



public:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<UBlueprint> Destroyer;
	
	virtual void IncreaseHealth(const float Value) override;
	virtual void DecreaseHealth(const float Value) override;
	const virtual float GetCurrentHealth() override { return Health; };
};
