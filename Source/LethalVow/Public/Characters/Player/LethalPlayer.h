// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/LethalCharacters.h"
#include "LethalPlayer.generated.h"

/**
 * 
 */
class UCameraComponent;
class UInputData;

UCLASS()
class LETHALVOW_API ALethalPlayer : public ALethalCharacters
{
	GENERATED_BODY()
	
public:

	ALethalPlayer(); 

protected:
	virtual void BeginPlay() override;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly,BLueprintReadOnly, Category = "Inputs",meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputData> InputData;

	UFUNCTION()
	void MovePlayer(const FInputActionValue& Value); 

	UFUNCTION()
	void Look(const FInputActionValue& Value); 

};
