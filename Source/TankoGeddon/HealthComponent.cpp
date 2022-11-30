// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


void UHealthComponent::TakeDamage(const FDamageData DamageData)
{
	const float TakeDamageValue = DamageData.DamageValue;
	CurrentHealth -= TakeDamageValue;

	if (CurrentHealth <= 0.0f)
	{
		if (OnDie.IsBound())
			OnDie.Broadcast();
	}
	else
	{
		if (OnHealthChanged.IsBound())
			OnHealthChanged.Broadcast(TakeDamageValue);		
	}
}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthState() const
{
	return  CurrentHealth/MaxHealth;
}

void UHealthComponent::AddHealth(float AddHealthValue)
{
	CurrentHealth += AddHealthValue;
	if(CurrentHealth>MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}