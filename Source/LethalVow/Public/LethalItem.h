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
	int32 Cost = 0.0f;
};

UCLASS()
class LETHALVOW_API ALethalItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ALethalItem();

	virtual void BeginPlay() override;

	void ToggleCollision(bool Collision);
private:
	FName ItemName;

	FName ItemDescription;

	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemsDataTable;
};
