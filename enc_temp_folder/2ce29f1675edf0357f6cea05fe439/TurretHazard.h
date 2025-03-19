// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretHazard.generated.h"

/**
 * 
 */
#pragma region Forward Declarations
class UAC_ObjectPool;
class USpotLightComponent;
class ALethalPlayer;
#pragma endregion
UCLASS()
class LETHALVOW_API ATurretHazard : public AActor
{
	GENERATED_BODY()
	
public:
	ATurretHazard();
	
	UFUNCTION(BlueprintPure)
	FRotator GetCurrentRotation() const { return CurrentRotation; }
protected:
	virtual void BeginPlay() override;

private:
	//UFUNCTION()
	//FHitResult& SearchForPlayer();

#pragma region Components

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Components|Light", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpotLightComponent> TurretLightComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Components|Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> TurretMesh;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Components|Object Pool", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAC_ObjectPool> ProjectilePool;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Mesh|Attach Socket",meta = (AllowPrivateAccess = true))
	FName SocketName;

#pragma endregion
#pragma region Light Colors
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Light",meta = (AllowPrivateAccess = true))
	FColor ActiveLightColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = true))
	FColor SeekingLightColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Light", meta = (AllowPrivateAccess = true))
	FColor AttackLightColor;
#pragma endregion
#pragma region Rotation
	bool bRotateClockwise;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotatation", meta = (AllowPrivateAccess = true))
	FRotator MaxRotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotatation", meta = (AllowPrivateAccess = true))
	FRotator MinRotation;
	void FlipRotation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotatation", meta = (AllowPrivateAccess = true))
	float TurnRate;

	void RotateTurret();
#pragma endregion
#pragma region Timers & tracking
	FTimerHandle RotateHandle;
	FTimerHandle ToggleHandle;
	FTimerHandle TrackingHandle;
	float ResetTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = true))
	float ResetTarget;

	TObjectPtr<ALethalPlayer> TrackedTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Distance", meta = (AllowPrivateAccess = true))
	float TraceDistance;
#pragma endregion

private:
	
	FRotator CurrentRotation; //it works better

	void MoveToTarget();

};
