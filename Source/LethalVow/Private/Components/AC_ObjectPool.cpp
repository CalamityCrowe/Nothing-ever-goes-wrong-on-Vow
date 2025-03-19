// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AC_ObjectPool.h"
#include "Projectiles/LethalProjectile.h"
// Sets default values for this component's properties
UAC_ObjectPool::UAC_ObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_ObjectPool::BeginPlay()
{
	Super::BeginPlay();

	InitializePool();
	// ...

}

/// <summary>
/// Finds the next avaialble actor 
/// </summary>
/// <returns></returns>
ALethalProjectile* UAC_ObjectPool::GetNextAvailableActor()
{
	bool NoActorAvailable = true;

	// loop through the pool to find an available actor and return it
	for (ALethalProjectile* projectile : Pool)
	{
		if (!projectile->IsInUse())
		{
			NoActorAvailable = false;
			return projectile;
		}
	}

	//if no actor is available, create a new one to add to the pool and increase the pool size
	if (NoActorAvailable)
	{
		PoolSize++;
		ALethalProjectile* temp = GetWorld()->SpawnActor<ALethalProjectile>(ActorToPool);
		if (temp)
		{
			temp->SetTimeToLive(TimeToLive);
#if UE_EDITOR
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Actor: %d"), PoolSize));
#endif // UE_EDITOR
			Pool.AddUnique(temp);
			return temp;
		}
	}
	return nullptr; // returns null if it can't find an available actor
}

void UAC_ObjectPool::InitializePool()
{
	if (PoolSize > 0)
	{
		Pool.Reserve(PoolSize); // this reserves the chunk of memory for the pool
	}
	for (int i = 0; i < PoolSize; ++i)
	{
		ALethalProjectile* temp = GetWorld()->SpawnActor<ALethalProjectile>(ActorToPool);
		if (temp)
		{
			temp->SetTimeToLive(TimeToLive);
			temp->SetInUse(false);
			Pool.AddUnique(temp);
		}
	}

}


// Called every frame
void UAC_ObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_ObjectPool::SpawnFromPool(FTransform trans)
{
	ALethalProjectile* projectile = GetNextAvailableActor();
	if (IsValid(projectile))
	{
		projectile->SetActorTransform(trans);
		projectile->SetInUse(true);
	}
}

