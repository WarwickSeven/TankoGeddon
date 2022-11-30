// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

UENUM()
enum class EWidgetID : uint8
{
	Wid_MainMenu = 0x0,
	Wid_EscapeMenu = 0x1,
	Wid_GameOverMenu = 0x3,
};

UCLASS()
class TANKOGEDDON_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	//set defaults values for this actor's properties
	AMainHUD();

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowWidget(const EWidgetID WidgetID, const int32 ZOrder = 0);

	UFUNCTION(BlueprintCallable)
	void HideWidget();

	UFUNCTION(BlueprintPure)
	UUserWidget* GetCurrentWidget() const { return CurrentWidget; }

protected:

	UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder = 0);

	UPROPERTY(EditAnywhere)
	TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
