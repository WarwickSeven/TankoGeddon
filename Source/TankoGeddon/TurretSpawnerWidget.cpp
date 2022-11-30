// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSpawnerWidget.h"

#include "TankController.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UTurretSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (DraggedText)
	{
		DraggedText->SetText(FText::FromString(DraggedName));
	}
}

void UTurretSpawnerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (auto* MyController = Cast<ATankController>(PlayerController))
	{
		MyController->OnMouseButtonUp.AddUObject(this, &ThisClass::OnMouseButtonUp);
	}
}

void UTurretSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnedActor && PlayerController)
	{
		FVector WorldMousePosition;
		FVector WorldMouseDirection;
		PlayerController->DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SpawnedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());

		FHitResult OutHit;
		constexpr float Dist = 100000.f;
		GetWorld()->LineTraceSingleByChannel(OutHit, WorldMousePosition, WorldMouseDirection + WorldMouseDirection * Dist, ECC_WorldStatic, Params);

		if (OutHit.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(OutHit.Location);
		}
	}
}

FReply UTurretSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnerClass);
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

// FReply UTurretSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
// {
// 	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
// 	{
// 		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnerClass);
// 	}
// 	return FReply::Handled();
// }

void UTurretSpawnerWidget::OnMouseButtonUp()
{
	SpawnedActor = nullptr;
}

