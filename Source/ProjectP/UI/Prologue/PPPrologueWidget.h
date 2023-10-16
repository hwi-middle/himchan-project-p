// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PPPrologueWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FSkipPrologueDelegate);

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPPrologueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FSkipPrologueDelegate SkipPrologueDelegate;
	
public:
	FORCEINLINE void SetPrologueText(const FText Text) const { PrologueText->SetText(Text); }
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SkipPrologue() { SkipPrologueDelegate.Broadcast(); }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PrologueText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SkipButton;
};
