// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"

ATankController::ATankController()
{
	bShowMouseCursor = true;	
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &ATankController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ATankController::MoveRight);
		InputComponent->BindAxis("RotateRight", this, &ATankController::RotateRight);
		InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATankController::Fire);
		InputComponent->BindAction("AlternateFire", EInputEvent::IE_Pressed, this, &ATankController::AlternateFire);
		//InputComponent->BindAction("BallisticAiming", EInputEvent::IE_Pressed, this, &ATankController::BallisticAiming);
		InputComponent->BindAxis("RotateTurretRight", this, &ATankController::RotateTurretRight);
		// InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ThisClass::OnLeftMouseButtonUp);
	}
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();
	bEnableClickEvents = true;
}

void ATankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	if (TankPawn)
	{
		FVector TankPosition = TankPawn->GetActorLocation();
		MousePos.Z = TankPosition.Z;
		FVector dir = MousePos - TankPosition;
		dir.Normalize();
		MousePos = TankPosition + dir * 1000.0f;
	}
	//DrawDebugLine(GetWorld(), TankPosition, MousePos, FColor::Green, false, 0.5f, 0, 5);
}

void ATankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	TankPawn = Cast<ATankPawn>(InPawn);
}

void ATankController::MoveForward(float Value)
{
	if (TankPawn)
		TankPawn->MoveForward(Value);
}

void ATankController::MoveRight(float Value)
{
	if (TankPawn)
		TankPawn->MoveRight(Value);
}

void ATankController::RotateRight(float Value)
{
	if (TankPawn)
		TankPawn->RotateRight(Value);
}

void ATankController::RotateTurretRight(float Value)
{
	if (TankPawn)
		TankPawn->RotateTurretRight(Value);
}

void ATankController::Fire()
{
	if (TankPawn)
		TankPawn->Fire();
}

void ATankController::AlternateFire()
{
	if (TankPawn)
		TankPawn->AlternateFire();
}

// void ATankController::OnLeftMouseButtonUp()
// {
// 	OnMouseButtonUp.Broadcast();
// }

// void ATankController::BallisticAiming()
// {
// 	if (TankPawn)
// 		TankPawn->BallisticAiming();
// }
