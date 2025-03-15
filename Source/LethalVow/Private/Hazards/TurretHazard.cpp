// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazards/TurretHazard.h"
#include "Components/SpotLightComponent.h"
#include "Components/CapsuleComponent.h"
#include "Characters/Player/LethalPlayer.h"
#include <Kismet/KismetMathLibrary.h>

ATurretHazard::ATurretHazard()
{
	PrimaryActorTick.bCanEverTick = true;

	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	RootComponent = TurretMesh;

	TurretLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("TurretLightComponent"));
	TurretLightComponent->SetupAttachment(TurretMesh);

	TraceDistance = 1000.0f;
}

void ATurretHazard::BeginPlay()
{
	Super::BeginPlay();
	TurretLightComponent->AttachToComponent(TurretMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	TurretLightComponent->AddLocalRotation(FRotator(90, 0, 0)); 
	CurrentRotation = TurretMesh->GetSocketRotation(SocketName);
	UE_LOG(LogTemp, Warning, TEXT("Yaw at Begin: %f"), CurrentRotation.Yaw);
	GetWorld()->GetTimerManager().SetTimer(RotateHandle, this, &ATurretHazard::RotateTurret, 0.05f, true);
}

void ATurretHazard::FlipRotation()
{
	bRotateClockwise = !bRotateClockwise;
	GetWorld()->GetTimerManager().ClearTimer(ToggleHandle);
}

void ATurretHazard::RotateTurret()
{

	FVector StartPos = GetActorLocation();
	FVector EndPos = StartPos + (TurretLightComponent->GetForwardVector() * TraceDistance);

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 0.05f, 0, 1.0f);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Pawn, QueryParams);

	if (Cast<ALethalPlayer>(Hit.GetActor()))
	{
		FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.GetActor()->GetActorLocation());
		CurrentRotation.Yaw = lookAt.Yaw;

		UE_LOG(LogTemp, Warning, TEXT("Player Found"));
		TurretLightComponent->SetLightColor(AttackLightColor);
	}
	else
	{
		TurretLightComponent->SetLightColor(ActiveLightColor);
		if (GetWorld()->GetTimerManager().IsTimerActive(ToggleHandle) == false)
		{
			if (bRotateClockwise)
			{
				CurrentRotation.Yaw = FMath::Clamp(CurrentRotation.Yaw + (GetWorld()->GetDeltaSeconds() * TurnRate), MinRotation.Yaw, MaxRotation.Yaw);
			}
			else
			{
				CurrentRotation.Yaw = FMath::Clamp(CurrentRotation.Yaw - (GetWorld()->GetDeltaSeconds() * TurnRate), MinRotation.Yaw, MaxRotation.Yaw);
			}
		}
		if (((CurrentRotation.Yaw <= MinRotation.Yaw) || (CurrentRotation.Yaw >= MaxRotation.Yaw)) && (GetWorld()->GetTimerManager().IsTimerActive(ToggleHandle) == false))
		{
			GetWorld()->GetTimerManager().SetTimer(ToggleHandle, this, &ATurretHazard::FlipRotation, 3.0f, false);
		}
	}


}
