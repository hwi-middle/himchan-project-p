// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PPPrologueWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPPrologueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetPrologueText(const FText Text) const { PrologueText->SetText(Text); }
	
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PrologueText;
};
