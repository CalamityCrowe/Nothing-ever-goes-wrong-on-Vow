// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LethalHazard.generated.h"

class UCapsuleComponent; 

UCLASS()
class LETHALVOW_API ALethalHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALethalHazard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UStaticMeshComponent* GetMesh() const { return Mesh.Get(); }
	UCapsuleComponent* GetCollider() const { return Collider.Get(); }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCapsuleComponent> Collider;

};
