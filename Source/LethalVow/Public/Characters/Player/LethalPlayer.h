// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/LethalCharacters.h"
#include "LethalItem.h"
#include "LethalPlayer.generated.h"

class UCameraComponent;
class UInputData;
class ULethalInventory;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHealthUpdated, float, Health);

UCLASS()
class LETHALVOW_API ALethalPlayer : public ALethalCharacters
{
	GENERATED_BODY()
	
public:
	ALethalPlayer();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemHoldSocketName = "ItemHold_Socket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ItemGrabRange = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CharacterHeight;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void DamageHealth(float DamageAmount) override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerHealthUpdated OnPlayerHealthUpdated;

	TObjectPtr<ALethalItem> GetHeldItem();

	void ResetHeldItem();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly,BLueprintReadOnly, Category = "Inputs",meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputData> InputData;

	TObjectPtr<USceneComponent> ItemHolderComponent;

	UPROPERTY(EditDefaultsOnly, BLueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<ULethalInventory> InventoryComponent;

	FTimerHandle SearchForItemTimerHandle;

	UFUNCTION()
	void MovePlayer(const FInputActionValue& Value); 

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void SearchForItem();

	void ShiftInventorySlot(const FInputActionValue& Value);

	void AttemptPickupItem();

	void DropItem();

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<ALethalItem> ItemLookingAt;

	void ToggleDebug();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bDebug = false;
};
