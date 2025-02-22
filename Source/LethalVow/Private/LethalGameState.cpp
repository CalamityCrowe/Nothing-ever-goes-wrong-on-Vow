// Fill out your copyright notice in the Description page of Project Settings.


#include "LethalGameState.h"

void ALethalGameState::UpdateUsingGamepad(bool bIsUsing)
{
	bIsUsingGamepad = bIsUsing;
}

void ALethalGameState::DepositItem(TObjectPtr<ALethalItem> ItemToDeposit)
{
	if (!ItemToDeposit)
	{
		return;
	}

	const FLethalItemConfig ItemConfig = ItemToDeposit->GetItemConfig();

	TotalScore += ItemConfig.ItemCost;

	ItemToDeposit->ConditionalBeginDestroy();
}