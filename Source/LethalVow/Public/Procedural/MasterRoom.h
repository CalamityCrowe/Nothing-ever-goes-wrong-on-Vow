// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterRoom.generated.h"

class UBoxComponent;

UCLASS()
class LETHALVOW_API AMasterRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<USceneComponent> GetExitsFolder() const { return ExitsFolder; }

	TObjectPtr<USceneComponent> GetOverlapFolder() const { return OverlapFolder; }

	TObjectPtr<USceneComponent> GetMeshFolder() const { return MeshFolder; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> ExitsFolder; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> OverlapFolder; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> MeshFolder;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Collisions")
	TObjectPtr<UBoxComponent> OverlapBox;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Components|Mesh")
	TObjectPtr<UStaticMeshComponent> FloorMesh;
};
