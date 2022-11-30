// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"

#include "HealthComponent.h"
#include "MapLoader.h"
#include "TankPawn.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ATankFactory::ATankFactory()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneComp);

		
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TankSpawnPoint"));
	TankSpawnPoint->SetupAttachment(BuildingMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankFactory::DamageTaked);
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
		
	DestroyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DestroyEffect"));
	DestroyEffect->SetupAttachment(BuildingMesh);
	DestroyAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("DestroyAudioEffect"));
	DestroyAudioEffect->SetupAttachment(BuildingMesh);

	UnitBuiltEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("UnitBuiltEffect"));
	UnitBuiltEffect->SetupAttachment(TankSpawnPoint);
	UnitBuiltAudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("UnitBuiltAudioEffect"));
	UnitBuiltAudioEffect->SetupAttachment(TankSpawnPoint);
}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();
	if (MapLoader)
	{
		MapLoader->SetIsActivated(false);
	}
	if (SpawnTankClass)
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ATankFactory::SpawnTank, SpawnTankRate, true, 2.0f);
	}
}

void ATankFactory::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (UStaticMesh* FactoryTempMesh = LoadObject<UStaticMesh>(this, *FactoryMeshPath))
		BuildingMesh->SetStaticMesh(FactoryTempMesh);
}

void ATankFactory::SpawnTank()
{
	FTransform SpawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	newTank->SetPatrollingPoints(TankWayPoints);

	UGameplayStatics::FinishSpawningActor(newTank, SpawnTransform);
	UnitBuiltEffect->ActivateSystem();
	UnitBuiltAudioEffect->Play();
}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankFactory::Die()
{
	if (MapLoader)
	{
		MapLoader->SetIsActivated(true);
	}
	DestroyEffect->ActivateSystem();
	DestroyAudioEffect->Play();

	if (UStaticMesh* DieMesh = LoadObject<UStaticMesh>(this, *DestroyedFactoryMeshPath))
		BuildingMesh->SetStaticMesh(DieMesh);
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	SetActorEnableCollision(false);
}

void ATankFactory::DamageTaked(float DamageValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("Factory %s take Damage: %f, Health: %f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}


