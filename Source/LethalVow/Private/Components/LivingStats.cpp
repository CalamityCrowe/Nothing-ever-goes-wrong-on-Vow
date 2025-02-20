// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LivingStats.h"

// Sets default values for this component's properties
ULivingStats::ULivingStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


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

