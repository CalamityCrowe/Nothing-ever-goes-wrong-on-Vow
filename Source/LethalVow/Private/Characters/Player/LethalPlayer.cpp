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

void ALethalPlayer::AttemptPickupItem()
{
	if (!HeldItem.IsNull())
	{
		return;
	}

	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FRotator CameraRotation = CameraComponent->GetComponentRotation();

	FVector ForwardVector = CameraRotation.Vector();

	// 1000 for a long ray, checking distance later
	FVector TraceEnd = CameraLocation + (ForwardVector * 1000.0f);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, TraceEnd, ECC_Visibility, QueryParams);

	FVector CharacterLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - CharacterHeight);

	if (bHit)
	{
		TObjectPtr<ALethalItem> ItemHit = Cast<ALethalItem>(Hit.GetActor());

		if (ItemHit && HeldItem.IsNull() && FVector::Dist(CharacterLocation, ItemHit->GetActorLocation()) <= ItemGrabRange)
		{
			ItemHit->ToggleCollision(false);

			ItemHit->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, ItemHoldSocketName);

			if (ItemHit->GetAttachParentSocketName() == ItemHoldSocketName)
			{
				HeldItem = ItemHit;
			}
		}
	}

#if UE_EDITOR
	if (bDebug)
	{
		DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 5.0f);
		DrawDebugSphere(GetWorld(), CharacterLocation, ItemGrabRange, 32, FColor(255, 0, 0, 128), false, 1.0f);
	}
#endif
}

void ALethalPlayer::DropItem(TObjectPtr<ALethalItem> ItemToDrop)
{
	ItemToDrop->ToggleCollision(true);

	ItemToDrop->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	if (ItemToDrop->GetAttachParentSocketName() != ItemHoldSocketName)
	{
		HeldItem = nullptr;
	}
}

void ALethalPlayer::ToggleDebug()
{
#if UE_EDITOR
	bDebug = !bDebug;
#endif
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
					for (TObjectPtr<UInputMappingContext> Context : InputData->Contexts)
					{
						InputSystem->AddMappingContext(Context, 0);
					}
				}
			}
		}
	}

	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PEI->BindAction(InputData->MovementActions[0], ETriggerEvent::Triggered, this, &ALethalPlayer::MovePlayer); 
		PEI->BindAction(InputData->MovementActions[1], ETriggerEvent::Triggered, this, &ALethalPlayer::Look);
		PEI->BindAction(InputData->MovementActions[2], ETriggerEvent::Triggered, this, &ACharacter::Jump);

		PEI->BindAction(InputData->InteractActions[0], ETriggerEvent::Triggered, this, &ALethalPlayer::AttemptPickupItem);
		PEI->BindAction(InputData->InteractActions[1], ETriggerEvent::Triggered, this, &ALethalPlayer::ToggleDebug);
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
