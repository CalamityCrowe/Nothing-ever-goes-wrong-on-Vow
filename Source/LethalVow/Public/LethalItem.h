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
};

UCLASS()
class LETHALVOW_API ALethalItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ALethalItem();

	virtual void BeginPlay() override;

private:
	FName ItemName;

	FName ItemDescription;

	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UDataTable* ItemsDataTable;
};
