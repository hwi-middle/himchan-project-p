// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectP/UI/PPUserWidget.h"
#include "ProjectP/UI/PPSettingWidget.h"
#include "PPLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPPLobbyWidget : public UPPUserWidget
{
	GENERATED_BODY()
public:
	UPPLobbyWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	
	// UI 바인딩
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> StartButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> SettingButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> HelpButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ExitButton;
	
	// UI에서 호출될 이벤트 함수
private:
	UFUNCTION(BlueprintCallable)
	void EntryMainLevel();
	
	UFUNCTION(BlueprintCallable)
	void OpenSettingWidget();

	UFUNCTION(BlueprintCallable)
	void OpenHelpWidget();

	UFUNCTION(BlueprintCallable)
	void OpenExitCheckWidget();

	// 위젯 이벤트에서 활성화/비활성화 할 서브위젯
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UPPSettingWidget> SettingWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<class UPPSettingWidget> HelpWidget;
};
