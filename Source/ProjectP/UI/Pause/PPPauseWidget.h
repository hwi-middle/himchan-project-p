// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectP/Constant/PPLevelName.h"
#include "ProjectP/Enumeration/PPSubWidgetType.h"
#include "PPPauseWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FResumeGameDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FPassSubWidgetTypeDelegate, ESubWidgetType);
DECLARE_MULTICAST_DELEGATE(FExitGameDelegate);

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FResumeGameDelegate ResumeGameDelegate;
	
	FPassSubWidgetTypeDelegate PassSubWidgetTypeDelegate;
	
	FExitGameDelegate ExitGameDelegate;
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ResumeGame() { ResumeGameDelegate.Broadcast(); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ActivateSettingWidget() { PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Setting); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ActivateExitWidget() { PassSubWidgetTypeDelegate.Broadcast(ESubWidgetType::Exit); }
	
	// Widget
	protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UButton> ResumeButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UButton> SettingButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<class UButton> ExitButton;
};
