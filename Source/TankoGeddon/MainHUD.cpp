// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

#include "Blueprint/UserWidget.h"

//Set default values

AMainHUD::AMainHUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AMainHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

UUserWidget* AMainHUD::ShowWidget(const EWidgetID WidgetID, const int32 ZOrder)
{
	HideWidget();

	TSubclassOf<UUserWidget>* ClassPtr = WidgetClasses.Find(WidgetID);
	if (ClassPtr && *ClassPtr)
	{
		CreateWidgetByClass(*ClassPtr, ZOrder);
	}
	
	return CurrentWidget;
}

void AMainHUD::HideWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

UUserWidget* AMainHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder)
{
	CurrentWidget = CreateWidget(GetOwningPlayerController(), WidgetClass);
	CurrentWidget->AddToViewport(ZOrder);	
	return CurrentWidget;
}
