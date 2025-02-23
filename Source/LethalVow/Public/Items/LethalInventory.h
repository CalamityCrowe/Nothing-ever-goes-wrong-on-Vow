// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LethalItem.h"
#include "LethalInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETHALVOW_API ULethalInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULethalInventory();

	UPROPERTY(EditDefaultsOnly)
	int32 InventorySize = 4;

	void ShiftSlot(float Direction);

	bool AttemptPickupItem(TObjectPtr<ALethalItem> ItemToPickup);

	TObjectPtr<ALethalItem> GetItemInCurrentSlot() { return Inventory[CurrentlySelectedSlot]; };

	bool IsItemInCurrentSlot() { return Inventory[CurrentlySelectedSlot] != nullptr; };

	void DropItem() { Inventory[CurrentlySelectedSlot] = nullptr; };
private:
	int32 CurrentlySelectedSlot = 0;

	TArray<TObjectPtr<ALethalItem>> Inventory;
};