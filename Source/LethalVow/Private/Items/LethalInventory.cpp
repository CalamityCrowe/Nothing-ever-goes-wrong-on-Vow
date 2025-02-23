#include "Items/LethalInventory.h"

ULethalInventory::ULethalInventory()
{
	for (int32 i = 0; i < InventorySize; i++)
	{
		Inventory.Add(nullptr);
	}
}

void ULethalInventory::ShiftSlot(float Direction)
{
	int32 LastSlot = CurrentlySelectedSlot;

	if (Direction > 0)
	{
		CurrentlySelectedSlot++;
	}
	else if (Direction < 0)
	{
		CurrentlySelectedSlot--;
	}

	if (CurrentlySelectedSlot < 0)
	{
		CurrentlySelectedSlot = Inventory.Num() - 1;
	}
	else if (CurrentlySelectedSlot == Inventory.Num())
	{
		CurrentlySelectedSlot = 0;
	}

	if (Inventory[LastSlot])
	{
		Inventory[LastSlot]->SetActorHiddenInGame(true);
	}

	if (Inventory[CurrentlySelectedSlot])
	{
		Inventory[CurrentlySelectedSlot]->SetActorHiddenInGame(false);
	}
}

bool ULethalInventory::AttemptPickupItem(TObjectPtr<ALethalItem> ItemToPickup)
{
	if (Inventory[CurrentlySelectedSlot] == nullptr)
	{
		Inventory[CurrentlySelectedSlot] = ItemToPickup;
		return true;
	}

	return false;
}
