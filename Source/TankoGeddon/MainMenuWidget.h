// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "MainMenuWidget.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainMenuDelegate, int32, SelectedButton);

UCLASS(Abstract)
class TANKOGEDDON_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UButton* NewGameBtn;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* QuitBtn;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* NewGameAnimation;

	UPROPERTY(BlueprintAssignable)
	FMainMenuDelegate OnButtonSelected;
	
	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnQuitClicked();

};
