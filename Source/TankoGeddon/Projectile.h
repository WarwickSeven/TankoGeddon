// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOGEDDON_API AProjectile : public AActor
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(AProjectile, FOnKill, float);
	
public:	
	AProjectile();
	virtual void Start();
	
	void Deactivate();
	bool bIsActivation = false;
	FOnKill OnKilled;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MoveRate = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float DeactivateTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bPhysicsEmulation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float PushForce = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bExplosionOnHit = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ExplodeRadius = 50.0f;
	
	FTimerHandle MoveTimer;
	FTimerHandle DeactivateTimer;
	
	virtual void Move();

	void MakeDamage(AActor* OtherActor);
	void UsePhysicsForce(AActor* OtherActor);
	void Explode();

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
