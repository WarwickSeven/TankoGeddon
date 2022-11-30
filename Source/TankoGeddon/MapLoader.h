// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "MapLoader.generated.h"

UCLASS()
class TANKOGEDDON_API AMapLoader : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapLoader();

	void SetIsActivated(bool NewIsActivated);

protected:
	virtual void BeginPlay() override;

	void SetActivatedLights();

	UFUNCTION()
    void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	class UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	UPointLightComponent* ActivatedLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	UPointLightComponent* DeactivatedLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	FName LoadLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	bool bIsActivated = false;
};