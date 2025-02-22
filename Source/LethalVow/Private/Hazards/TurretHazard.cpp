// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazards/TurretHazard.h"
#include "Components/SpotLightComponent.h"
#include "Characters/Player/LethalPlayer.h"
#include <Kismet/KismetMathLibrary.h>

ATurretHazard::ATurretHazard()
{
	TurretLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("TurretLightComponent"));
	TurretLightComponent->SetupAttachment(GetMesh());

	SpotLightCollision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpotLightCollision"));
	SpotLightCollision->SetupAttachment(TurretLightComponent);



	TraceDistance = 1000.0f;
}

void ATurretHazard::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(RotateHandle, this, &ATurretHazard::RotateTurret, 0.1f, true);
}

//FHitResult& ATurretHazard::SearchForPlayer()
//{
//
//
//}



void ATurretHazard::FlipRotation()
{
	bRotateClockwise = !bRotateClockwise;
	GetWorld()->GetTimerManager().ClearTimer(ToggleHandle);
}

void ATurretHazard::RotateTurret()
{

	FVector StartPos = GetActorLocation();
	FVector EndPos = StartPos + (GetMesh()->GetForwardVector() * TraceDistance);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Pawn, QueryParams);

#if UE_EDITOR
	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 0.1f, 0, 1.0f);
#endif
	if (Cast<ALethalPlayer>(Hit.GetActor()))
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.GetActor()->GetActorLocation());
		FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), TurnRate);
		GetMesh()->SetWorldRotation(CurrentRotation);
		TurretLightComponent->SetWorldRotation(GetMesh()->GetComponentRotation());
		TurretLightComponent->SetLightColor(AttackLightColor);
		//TurretLightComponent
	}
	else
	{
		FRotator CurrentRotation = GetActorRotation();
		if (bRotateClockwise && CurrentRotation.Yaw <= MaxRotation.Yaw)
		{
			CurrentRotation = GetMesh()->GetComponentRotation() + FRotator(0, GetWorld()->GetDeltaSeconds() * TurnRate, 0);

		}
		else
		{
			CurrentRotation = GetMesh()->GetComponentRotation() - FRotator(0, GetWorld()->GetDeltaSeconds() * TurnRate, 0);

			//bRotateClockwise = true;
		}
		if (((CurrentRotation.Yaw <= MinRotation.Yaw) || (CurrentRotation.Yaw >= MaxRotation.Yaw)) && (GetWorld()->GetTimerManager().IsTimerActive(ToggleHandle) == false))
		{
			GetWorld()->GetTimerManager().SetTimer(ToggleHandle, this, &ATurretHazard::FlipRotation, 3.0f, false);
		}
		GetMesh()->SetWorldRotation(CurrentRotation);
		TurretLightComponent->SetWorldRotation(GetMesh()->GetComponentRotation());
	}
}
