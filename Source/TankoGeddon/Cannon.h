// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "PhysicsComponent.h"
#include "TankPawn.h"
#include "Camera/CameraShakeBase.h"
#include "Cannon.generated.h"


class AProjectilePool;
UCLASS()
class TANKOGEDDON_API ACannon final : public AActor
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(ACannon, FChangeScore, float);
	
public:	
	ACannon();
	void Fire();
	void AlternateFire();
	void MainReload();
	void AlternateReload();
	
	bool IsReadyToFire() const { return bMainCanFire; };	
	void CreateProjectilePool();

	int GetCurrentAmmoValue() const { return CurrentAmmo; };
	int GetMaxAmmoValue() const { return MaxAmmo; };
	void IncreaseAmmoValue(const int AmmoValue);

	//Score
	float Score = 0.0f;

	UFUNCTION()
	void AddScore(float ScoreValue);
	
	FChangeScore ScoreChanged;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	ECannonType CannonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int BurstFireRate = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float BurstFireInterval = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float FireRange = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float TraceDamage = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int MaxAmmo = 120;

	int CurrentAmmo;
	
	FTimerHandle ReloadTimer;
	FTimerHandle BurstFireTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<AProjectilePool> ProjectilePoolClass;

	UPROPERTY()
	AProjectilePool* ProjectilePool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* ShootEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UAudioComponent* AudioEffect;

	//Feedback
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    UForceFeedbackEffect * ShootForceEffect;
    UPROPERTY(EditAnywhere)
    TSubclassOf<UCameraShakeBase> ShootShake;

	//Ballistic Aiming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPhysicsComponent* PhysicsComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ballistic Aiming")
	float MaxTimeSimulation = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ballistic Aiming")
	float TimeStep = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ballistic Aiming")
	float MoveSpeedPhysics = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ballistic Aiming")
	FVector MoveVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ballistic Aiming")
	TArray<FVector> CurrentTrajectory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ballistic Aiming")
	int32 TrajectoryPointIndex;
	
private:
	bool bMainCanFire = true;
	bool bAlternateCanFire = true;
	int CurrentShot;
	void BurstFire();
};
