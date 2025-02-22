// Fill out your copyright notice in the Description page of Project Settings.


#include "LethalItem.h"

// Sets default values
ALethalItem::ALethalItem()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ALethalItem::BeginPlay()
{
	if (FMath::RandRange(0, 100) <= ChanceToSpawn)
	{
		TArray<FName> RowNames = ItemsDataTable->GetRowNames();

		if (RowNames.Num() > 0)
		{
			int32 TotalWeight = 0;
			TArray<int32> Weights;

			for (const FName& RowName : RowNames)
			{
				FLethalItemConfig* Config = ItemsDataTable->FindRow<FLethalItemConfig>(RowName, TEXT(""));

				if (Config)
				{
					int32 Weight = 100 - Config->ItemRarity;
					TotalWeight += Weight;
					Weights.Add(Weight);
				}
				else
				{
					Weights.Add(0);
				}
			}

			int32 RandomWeight = FMath::RandRange(0, TotalWeight - 1);
			int32 SelectedIndex = 0;

			for (int32 i = 0; i < Weights.Num(); i++)
			{
				RandomWeight -= Weights[i];

				if (RandomWeight < 0)
				{
					SelectedIndex = i;
					break;
				}
			}

			FName RandomRowName = RowNames[SelectedIndex];
			ItemConfig = ItemsDataTable->FindRow<FLethalItemConfig>(RandomRowName, TEXT(""));

			if (ItemConfig)
			{
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
	else
	{
		ConditionalBeginDestroy();
	}
}

void ALethalItem::ToggleCollision(bool Collision)
{
	if (Collision)
	{
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	StaticMeshComponent->SetSimulatePhysics(Collision);
}