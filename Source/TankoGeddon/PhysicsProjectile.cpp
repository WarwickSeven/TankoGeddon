// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsProjectile.h"
#include "DamageTaker.h"
#include "PhysicsComponent.h"
#include "DrawDebugHelpers.h"
#include "GameStruct.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

APhysicsProjectile::APhysicsProjectile()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>(TEXT("PhysicsComponent"));
	
	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(RootComponent);
}

void APhysicsProjectile::Start()
{
	MoveVector = GetActorForwardVector() * MoveSpeedPhysics;
	CurrentTrajectory = PhysicsComponent->GenerateTrajectory(GetActorLocation(), MoveVector, MaxTimeSimulation, TimeStep, 0.0f);

	if (bShowTrajectory)
	{
		for (FVector position : CurrentTrajectory)
		{
			DrawDebugSphere(GetWorld(), position, 5, 8, FColor::Purple, true, 1, 0, 2);
		}
	}
	TrajectoryPointIndex = 0;
	TrailEffect->ActivateSystem();
	Super::Start();
}

void APhysicsProjectile::Move()
{
	FVector CurrentMoveVector = CurrentTrajectory[TrajectoryPointIndex] - GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Not normalize: %s"), *CurrentMoveVector.ToString());
	CurrentMoveVector.Normalize();
	//UE_LOG(LogTemp, Warning, TEXT("Normalize: %s"), *CurrentMoveVector.ToString());
	
	FVector newLocation = GetActorLocation() + CurrentMoveVector * MoveSpeed * MoveRate;
	SetActorLocation(newLocation);

	if (FVector::Distance(newLocation, CurrentTrajectory[TrajectoryPointIndex]) <= MovementAccuracy)
	{
		TrajectoryPointIndex++;
		if (TrajectoryPointIndex >= CurrentTrajectory.Num())
		{
			if (bExplosionOnHit)
				Explode();

			Destroy();
		}
		else
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTrajectory[TrajectoryPointIndex]);
			SetActorRotation(newRotation);
		}
	}
}
