// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameBtn)
	{
		NewGameBtn->OnPressed.AddDynamic(this, &ThisClass::OnNewGameClicked);
	}

	if (QuitBtn)
	{
		QuitBtn->OnPressed.AddDynamic(this, &ThisClass::OnQuitClicked);
	}
}

void UMainMenuWidget::NativeDestruct()
{
	if (NewGameBtn)
	{
		NewGameBtn->OnPressed.RemoveAll(this);
	}

	if (QuitBtn)
	{
		QuitBtn->OnPressed.RemoveAll(this);
	}
	
	Super::NativeDestruct();
}

void UMainMenuWidget::OnNewGameClicked()
{
	if (NewGameAnimation)
	{
		PlayAnimation(NewGameAnimation);
	}
	OnButtonSelected.Broadcast(0);
}

void UMainMenuWidget::OnQuitClicked()
{
	//GEngine->Exec(GetWorld(), TEXT("Quit"));
	OnButtonSelected.Broadcast(1);
}
