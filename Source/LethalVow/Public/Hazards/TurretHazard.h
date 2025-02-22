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

	UPROPERTY(EditDefaultsOnly,BLueprintReadOnly,Category = "Light",meta = (AllowPrivateAccess = true))
	FColor ActiveLightColor;
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = true))
	FColor SeekingLightColor;
	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = true))
	FColor AttackLightColor;

	
 

	FTimerHandle TimerHandle;
	float TurnRate;

protected:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	
	void RotateTurret();
	ALethalPlayer* PlayerRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Distance", meta = (AllowPrivateAccess = true))
	float TraceDistance;



};
