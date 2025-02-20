// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LethalCharacters.generated.h"

class ULivingStats;
class UCameraComponent; 
UCLASS()
class LETHALVOW_API ALethalCharacters : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALethalCharacters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void DamageHealth(float DamageAmount); 
	
	UFUNCTION()
	virtual bool IsAlive() const;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	TObjectPtr<ULivingStats> StatsComponent;
	
};
