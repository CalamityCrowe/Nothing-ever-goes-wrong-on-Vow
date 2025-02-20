// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LivingStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETHALVOW_API ULivingStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULivingStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void DamageHealth(float DamageAmount);
	void RecoverHealth(float RecoverAmount);

	void ResetHealth() { Health = MaxHealth; }
	bool IsAlive() { return bIsAlive; }
	float GetHealth() { return Health; }
	float GetMaxHealth() { return MaxHealth; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Stats|Health", meta = (AllowPrivateAccess = true))
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats|Health", meta = (AllowPrivateAccess = true))
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats|Health", meta = (AllowPrivateAccess = true))
	bool bIsAlive;		
};
