// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hazards/LethalHazard.h"
#include "TurretHazard.generated.h"

/**
 * 
 */

class USpotLightComponent;
class ALethalPlayer;
UCLASS()
class LETHALVOW_API ATurretHazard : public ALethalHazard
{
	GENERATED_BODY()
	
public:
	ATurretHazard();

protected:
	virtual void BeginPlay() override;

private:
	//UFUNCTION()
	//FHitResult& SearchForPlayer();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpotLightComponent> TurretLightComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> SpotLightCollision;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Light",meta = (AllowPrivateAccess = true))
	FColor ActiveLightColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = true))
	FColor SeekingLightColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = true))
	FColor AttackLightColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotatation", meta = (AllowPrivateAccess = true))
	FRotator MaxRotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotatation", meta = (AllowPrivateAccess = true))
	FRotator MinRotation;
 

	FTimerHandle RotateHandle;
	FTimerHandle ToggleHandle;

	void FlipRotation(); 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotatation", meta = (AllowPrivateAccess = true))
	float TurnRate;

	void RotateTurret();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Distance", meta = (AllowPrivateAccess = true))
	float TraceDistance;

	bool bRotateClockwise;

private:
	


};
