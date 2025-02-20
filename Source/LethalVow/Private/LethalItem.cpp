// Fill out your copyright notice in the Description page of Project Settings.


#include "LethalItem.h"

// Sets default values
ALethalItem::ALethalItem()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));

	SetRootComponent(StaticMeshComponent);
}

void ALethalItem::BeginPlay()
{
	TArray<FName> RowNames = ItemsDataTable->GetRowNames();

	if (RowNames.Num() > 0)
	{
		FName RandomRowName = RowNames[FMath::RandRange(0, RowNames.Num() - 1)];
		FLethalItemConfig* ItemConfig = ItemsDataTable->FindRow<FLethalItemConfig>(RandomRowName, TEXT(""));

		if (ItemConfig)
		{
			ItemName = ItemConfig->ItemName;
			ItemDescription = ItemConfig->ItemDescription;
			StaticMeshComponent->SetStaticMesh(ItemConfig->ItemMesh);
			
			SetActorScale3D(FVector(ItemConfig->ItemScale, ItemConfig->ItemScale, ItemConfig->ItemScale));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to find row: %s in DataTable: %s"), *RandomRowName.ToString(), *ItemsDataTable->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No rows in table, set it up, dumbass."));
	}
}