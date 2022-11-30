// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MachinePawn.h"
#include "Components/WidgetInteractionComponent.h"
//#include "Components/WidgetComponent.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class ACannon;
class ATargetPoint;
class UWidgetComponent;

UCLASS()
class TANKOGEDDON_API ATankPawn final : public AMachinePawn
{
	GENERATED_BODY()
	
public:
	ATankPawn();
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);
	void RotateTurretRight(float Value);

	virtual void Tick(float DeltaSeconds) override;

	//AI
	UFUNCTION()
	TArray<FVector> GetPatrollingPoints();

	void SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints);
	
	UFUNCTION()
	float GetMovementAccuracy() { return MovementAccuracy; }

	UFUNCTION()
	FVector GetTurretForwardVector();

	UFUNCTION()
	void RotateTurretTo(FVector TargetPosition);

	FVector GetEyesPosition();

	/* 3D HealthBar
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HealthWidget;

	UPROPERTY(BlueprintReadOnly)
	UWidgetInteractionComponent* WidgetInteract;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UWidgetComponent* WidgetComp;
	*/
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float MoveSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float InterpolationKey = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float RotateSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float RotateInterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float TurretRotateSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float TurretRotateInterpolationKey = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	bool bMouseControl = true;
	
	UPROPERTY()
	class ATankController* TankController;
		
	//AI Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI | Components", Meta = (MakeEditWidget = true))
	TArray<ATargetPoint*> PatrollingPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI | Components")
	float MovementAccuracy = 30.0f;
	
private:	
	float TargetForwardAxisValue = 0.0f;
	float TargetRightAxisValue = 0.0f;
	float RotateRightAxisValue = 0.0f;
	float RotateTurretRightAxisValue = 0.0f;
	float CurrentRotateAxisValue = 0.0f;
	float CurrentTurretRotateAxisValue = 0.0f;
};