// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "TankFactory.generated.h"

UCLASS()
class TANKOGEDDON_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	ATankFactory();

	UFUNCTION()
	virtual void TakeDamage(FDamageData DamageData) override;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	
	void SpawnTank();
			
	UFUNCTION()
	void DamageTaked(float DamageValue);

	UFUNCTION()
	void Die();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	class UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	class UArrowComponent* TankSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	TSubclassOf<class ATankPawn> SpawnTankClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	float SpawnTankRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Parameters")
	TArray<ATargetPoint*> TankWayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MapLoader")
	class AMapLoader* MapLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* DestroyEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UAudioComponent* DestroyAudioEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UParticleSystemComponent* UnitBuiltEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UAudioComponent* UnitBuiltAudioEffect;

	const FString FactoryMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_Factory.SM_Factory'";

	const FString DestroyedFactoryMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_FactoryDestroyed.SM_FactoryDestroyed'";
	
private:
	FTimerHandle SpawnTimer;
};
