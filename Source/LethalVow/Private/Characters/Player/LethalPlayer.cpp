// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/LethalPlayer.h"
#include "Camera/CameraComponent.h"

#include "DataAssets/InputData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

ALethalPlayer::ALethalPlayer() :ALethalCharacters()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	ItemHolderComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ItemHolderComponent"));
	ItemHolderComponent->SetupAttachment(GetRootComponent());
}

void ALethalPlayer::PickupItem(TObjectPtr<ALethalItem> ItemToPickup)
{
	ItemToPickup->ToggleCollision(false);

	ItemToPickup->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, FName("ItemHold_Socket"));
}

void ALethalPlayer::DropItem(TObjectPtr<ALethalItem> ItemToDrop)
{
	ItemToDrop->ToggleCollision(true);

	ItemToDrop->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void ALethalPlayer::BeginPlay()
{
	ALethalCharacters::BeginPlay();
}

void ALethalPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent) 
	{
		if (APlayerController* PC = Cast<APlayerController>(Controller)) 
		{
			if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer()) 
			{
				if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
				{
					InputSystem->AddMappingContext(InputData->Contexts[0], 0); 
				}
			}
		}
	}

	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PEI->BindAction(InputData->MovementActions[0], ETriggerEvent::Triggered, this, &ALethalPlayer::MovePlayer); 
		PEI->BindAction(InputData->MovementActions[1], ETriggerEvent::Triggered, this, &ALethalPlayer::Look);
		PEI->BindAction(InputData->MovementActions[2], ETriggerEvent::Triggered, this, &ACharacter::Jump);
	}
}

void ALethalPlayer::MovePlayer(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(),Movement.Y);
	AddMovementInput(GetActorRightVector(), Movement.X);
	
}

void ALethalPlayer::Look(const FInputActionValue& Value)
{
	FVector2D Look = Value.Get<FVector2D>();
	AddControllerPitchInput(Look.Y);
	AddControllerYawInput(Look.X);
}
