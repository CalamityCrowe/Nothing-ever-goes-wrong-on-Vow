// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LivingStats.h"

// Sets default values for this component's properties
ULivingStats::ULivingStats()
{
	Health = 100.0f;
	MaxHealth = 100.0f; 
	bIsAlive = true;
	// ...
}


// Called when the game starts
void ULivingStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void ULivingStats::DamageHealth(float DamageAmount)
{
	Health -= DamageAmount;
	if(Health <= 0)
	{
		bIsAlive = false;
	}
	
}
void ULivingStats::RecoverHealth(float RecoverAmount) 
{
	Health += RecoverAmount;
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

