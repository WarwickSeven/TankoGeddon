// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"

#include "PhysicsComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"
#include "PhysicsProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"


DECLARE_LOG_CATEGORY_EXTERN(LogTank, All, All);
DEFINE_LOG_CATEGORY(LogTank);

ATankPawn::ATankPawn()
{
 	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATankPawn::MoveForward(const float Value)
{
	TargetForwardAxisValue = Value;	
}

void ATankPawn::MoveRight(const float Value)
{
	TargetRightAxisValue = Value;
}

void ATankPawn::RotateRight(const float Value)
{
	RotateRightAxisValue = Value;
}

void ATankPawn::RotateTurretRight(float Value)
{
	RotateTurretRightAxisValue = Value;
}

void ATankPawn::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Tank Movement
	const FVector CurrentLocation = GetActorLocation();
	const FVector ForwardVector = GetActorForwardVector();
	const FVector RightVector = GetActorRightVector();
	const FVector MovePosition = CurrentLocation + (ForwardVector * MoveSpeed * TargetForwardAxisValue) + (RightVector * MoveSpeed * TargetRightAxisValue);
	SetActorLocation(MovePosition, true);

	//Tank Rotation
	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, RotateRightAxisValue, InterpolationKey);
	float YawRotation = RotateSpeed * CurrentRotateAxisValue * DeltaSeconds;
	const FRotator CurrentRotation = GetActorRotation();
	YawRotation += CurrentRotation.Yaw;
	const FRotator NewRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(NewRotation);

	//Player Turret Rotation GamePad
	CurrentTurretRotateAxisValue = FMath::Lerp(CurrentTurretRotateAxisValue, RotateTurretRightAxisValue, TurretRotateInterpolationKey);
	float YawTurretRotation = TurretRotateSpeed * CurrentTurretRotateAxisValue * DeltaSeconds;
	const FRotator CurrentTurretRotation = TurretMesh->GetComponentRotation();
	YawTurretRotation += CurrentTurretRotation.Yaw;
	const FRotator NewTurretRotation = FRotator(0.0f, YawTurretRotation, 0.0f);
	const FRotator TurretRotation = TurretMesh->GetComponentRotation();
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, NewTurretRotation, TurretRotateInterpolationKey));

	//UE_LOG(LogTemp, Warning, TEXT("CurrentRotateAxis Value: %f, RotateRightAxisValue: %f, "), CurrentRotateAxisValue, RotateRightAxisValue);

	//Player Turret Rotation Mouse
	if (TankController && bMouseControl == true)
	{
		FVector MousePos = TankController->GetMousePosition();
		RotateTurretTo(MousePos);
	}
}

TArray<FVector> ATankPawn::GetPatrollingPoints()
{
	TArray<FVector> points;
	for (ATargetPoint* point : PatrollingPoints)
	{
		 points.Add(point->GetActorLocation());
	}
	return points;
}

void ATankPawn::SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints)
{
	PatrollingPoints = NewPatrollingPoints;
}

FVector ATankPawn::GetTurretForwardVector()
{
	return TurretMesh->GetForwardVector();
}

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator TurretRotation = TurretMesh->GetComponentRotation();

	TargetRotation.Pitch = TurretRotation.Pitch;
	TargetRotation.Roll = TurretRotation.Roll;

	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, TargetRotation, RotateInterpolationKey));
}

FVector ATankPawn::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));

	TankController = Cast<ATankController>(GetController());
}

