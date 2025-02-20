// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazards/LandmineHazard.h"
#include "Characters/LethalCharacters.h"


ALandmineHazard::ALandmineHazard()
{
}

void ALandmineHazard::BeginPlay()
{
	Super::BeginPlay(); 

}

void ALandmineHazard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ALethalCharacters* tempCharacter =  Cast<ALethalCharacters>(OtherActor)) 
	{
		if (tempCharacter->ActorHasTag("Player") && tempCharacter->IsAlive()) // checks if it is the player and they are alive
		{
			bArmed = true;
		}
	}
}

void ALandmineHazard::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ALethalCharacters* tempCharacter = Cast<ALethalCharacters>(OtherActor))
	{
		if(bArmed)
		{
			// do the logic for triggering the explosion here
		}
	}
}
