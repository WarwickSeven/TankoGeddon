// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

UCLASS()
class TANKOGEDDON_API ATankController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankController();
	virtual void SetupInputComponent() override;

	UPROPERTY()
	class ATankPawn* TankPawn;

	UPROPERTY()
	FVector MousePos = FVector::Zero();

	FVector GetMousePosition() { return MousePos; }

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds);
	
	virtual void SetPawn(APawn* InPawn) override;

	FSimpleMulticastDelegate OnMouseButtonUp;
	
protected:
	UFUNCTION()
	void MoveForward(float Value);
	
	UFUNCTION()
	void MoveRight(float Value);
	
	UFUNCTION()
	void RotateRight(float Value);

	UFUNCTION()
	void RotateTurretRight(float Value);

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void AlternateFire();

	void OnLeftMouseButtonUp();
	
	// UFUNCTION()
	// void BallisticAiming();
};
