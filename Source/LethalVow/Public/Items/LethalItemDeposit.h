// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LethalItemDeposit.generated.h"

UCLASS()
class LETHALVOW_API ALethalItemDeposit : public AActor
{
	GENERATED_BODY()
	
public:	
	ALethalItemDeposit();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "100"))
	int32 ChanceToSpawn = 100;

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<UBoxComponent> OverlapCollider;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
