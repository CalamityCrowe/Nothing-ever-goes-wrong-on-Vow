// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LethalCharacters.h"
#include "Components/LivingStats.h"

// Sets default values
ALethalCharacters::ALethalCharacters()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALethalCharacters::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ALethalCharacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALethalCharacters::DamageHealth(float DamageAmount)
{
	StatsComponent->DamageHealth(DamageAmount);
}

bool ALethalCharacters::IsAlive() const
{
	return StatsComponent->IsAlive();
}

