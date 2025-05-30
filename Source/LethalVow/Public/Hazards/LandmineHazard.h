// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hazards/LethalHazard.h"
#include "LandmineHazard.generated.h"

/**
 * 
 */
UCLASS()
class LETHALVOW_API ALandmineHazard : public ALethalHazard
{
	GENERATED_BODY()
public:
	ALandmineHazard();

protected:
	virtual void BeginPlay() override;

	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;

	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) ;

private:
	bool bArmed;
};
