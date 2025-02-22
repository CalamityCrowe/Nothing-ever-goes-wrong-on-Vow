// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/LethalItemDeposit.h"
#include "Characters/Player/LethalPlayer.h"
#include "LethalItem.h"
#include "LethalGameState.h"

ALethalItemDeposit::ALethalItemDeposit()
{
	OverlapCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCollider"));
	OverlapCollider->SetupAttachment(GetRootComponent());
	OverlapCollider->SetCollisionProfileName("OverlapAll");

	OverlapCollider->OnComponentBeginOverlap.AddDynamic(this, &ALethalItemDeposit::OnOverlapBegin);
}

void ALethalItemDeposit::BeginPlay()
{
	if (FMath::RandRange(0, 100) > ChanceToSpawn)
	{
		ConditionalBeginDestroy();
	}
}

void ALethalItemDeposit::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ALethalPlayer> LethalPlayer = Cast<ALethalPlayer>(OtherActor);

	if (LethalPlayer)
	{
		if (TObjectPtr<ALethalItem> HeldItem = LethalPlayer->GetHeldItem())
		{
			if (TObjectPtr<ALethalGameState> LethalGameState = Cast<ALethalGameState>(GetWorld()->GetGameState()))
			{
				LethalGameState->DepositItem(HeldItem);
				LethalPlayer->ResetHeldItem();
			}
		}
	}
}