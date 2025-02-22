// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LethalItem.generated.h"

USTRUCT(BlueprintType)
struct FLethalItemConfig : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ItemScale = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ItemCost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "100"))
	int32 ItemRarity = 0;
};

UCLASS()
class LETHALVOW_API ALethalItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ALethalItem();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "100"))
	int32 ChanceToSpawn = 100;

	void ToggleCollision(bool Collision);

	UFUNCTION(BlueprintCallable)
	const FLethalItemConfig& GetItemConfig() { return *ItemConfig; }
private:
	FLethalItemConfig* ItemConfig;

	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemsDataTable;
};
