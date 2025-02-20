// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputData.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class LETHALVOW_API UInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs|Contexts")
	TArray<TObjectPtr<UInputMappingContext>> Contexts;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs|Movement")
	TArray<TObjectPtr<UInputAction>> MovementActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs|Movement")
	TArray<TObjectPtr<UInputAction>> AttackActions;
};
