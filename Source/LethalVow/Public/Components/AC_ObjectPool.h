// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_ObjectPool.generated.h"

class ALethalProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LETHALVOW_API UAC_ObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_ObjectPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ALethalProjectile* GetNextAvailableActor();

	virtual void InitializePool();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPoolSize(int Size) { PoolSize = Size; }
	void SetTimeTOLive(float Time) { TimeToLive = Time; }
	void SpawnFromPool(FTransform trans);
	// Spawn an object from the pool

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<ALethalProjectile> ActorToPool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int PoolSize = 5;

	TArray<TObjectPtr<ALethalProjectile>> Pool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float TimeToLive = 5.0f;

};
