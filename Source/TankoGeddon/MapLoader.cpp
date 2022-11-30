// Fill out your copyright notice in the Description page of Project Settings.


#include "MapLoader.h"

#include "TankPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AMapLoader::AMapLoader()
{
 	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;
	
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(SceneComponent);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ActivatedLights"));
	ActivatedLight->SetupAttachment(SceneComponent);
	
	DeactivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("DeactivatedLights"));
	DeactivatedLight->SetupAttachment(SceneComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(SceneComponent);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMapLoader::OnTriggerOverlapBegin);
}

void AMapLoader::SetIsActivated(bool NewIsActivated)
{
	bIsActivated = NewIsActivated;
	SetActivatedLights();
}

void AMapLoader::BeginPlay()
{
	Super::BeginPlay();
	SetActivatedLights();
}

void AMapLoader::SetActivatedLights()
{
	ActivatedLight->SetHiddenInGame(!bIsActivated);
	DeactivatedLight->SetHiddenInGame(bIsActivated);
}

void AMapLoader::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bIsActivated)
	{
		return;
	}
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if(TankPawn)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}
}	
	
