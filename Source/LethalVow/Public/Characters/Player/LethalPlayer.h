// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/LethalCharacters.h"
#include "LethalItem.h"
#include "LethalPlayer.generated.h"

class UCameraComponent;
class UInputData;

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

protected:
	virtual void BeginPlay() override;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void DamageHealth(float DamageAmount) override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerHealthUpdated OnPlayerHealthUpdated;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly,BLueprintReadOnly, Category = "Inputs",meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputData> InputData;

	TObjectPtr<USceneComponent> ItemHolderComponent;

	UFUNCTION()
	void MovePlayer(const FInputActionValue& Value); 

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	void AttemptPickupItem();

	void DropItem(TObjectPtr<ALethalItem> ItemToDrop);

	TObjectPtr<ALethalItem> HeldItem;

	void ToggleDebug();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bDebug = false;
};
