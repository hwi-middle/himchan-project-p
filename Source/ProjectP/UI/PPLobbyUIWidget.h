// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPLobbyUIBaseActor.h"
#include "Blueprint/UserWidget.h"
#include "PPLobbyUIWidget.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTP_API UPPLobbyUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<APPLobbyUIBaseActor> LobbyUIBaseActor;
	
	UFUNCTION(BlueprintCallable)
	void EntryMainLevel();
	
	UFUNCTION(BlueprintCallable)
	void ToggleSettingWidget();

	UFUNCTION(BlueprintCallable)
	void ToggleHelpWidget();

	UFUNCTION(BlueprintCallable)
	void OpenExitCheckWidget();
	
	// 
protected:
	virtual void NativeConstruct() override;

	// Widget
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> StartButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> SettingButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> HelpButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ExitButton;
	
};
