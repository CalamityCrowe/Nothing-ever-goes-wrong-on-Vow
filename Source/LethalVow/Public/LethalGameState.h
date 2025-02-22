// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LethalItem.h"
#include "LethalGameState.generated.h"

UCLASS()
class LETHALVOW_API ALethalGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsUsingGamepad = false;

	UFUNCTION(BlueprintCallable)
	void UpdateUsingGamepad(bool bIsUsing);

	void DepositItem(TObjectPtr<ALethalItem> ItemToDeposit);
private:
	int32 TotalScore = 0;
};
