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

	FVector StartPos = TurretMesh->GetSocketLocation(SocketName);
	FVector EndPos = StartPos + (TurretLightComponent->GetForwardVector() * TraceDistance);

	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 0.05f, 0, 1.0f);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Pawn, QueryParams);

	if (Cast<ALethalPlayer>(Hit.GetActor()))
	{
		TrackedTarget = Cast<ALethalPlayer>(Hit.GetActor());
		GetWorld()->GetTimerManager().SetTimer(TrackingHandle, this, &ATurretHazard::MoveToTarget, 0.0f, true);
	}
	else
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(TrackingHandle))
		{
			UE_LOG(LogTemp, Warning, TEXT("Tracking"));
			if(!Cast<ALethalPlayer>(Hit.GetActor()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Lost Target"));
				ResetTimer += GetWorld()->GetDeltaSeconds();
				if (ResetTimer >= ResetTarget)
				{
					UE_LOG(LogTemp, Warning, TEXT("Reset Target"));
					TrackedTarget = nullptr;
					ResetTimer = 0.0f;
					GetWorld()->GetTimerManager().ClearTimer(TrackingHandle);
				}
			}
		}
		else
		{
			ResetTimer = 0.0f;

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


}

void ATurretHazard::MoveToTarget()
{
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetSocketLocation(SocketName), TrackedTarget->GetActorLocation());
	
	FRotator NewRotation = FMath::RInterpTo(TurretMesh->GetSocketRotation(SocketName), TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
	CurrentRotation.Yaw = FMath::Clamp(NewRotation.Yaw, MinRotation.Yaw, MaxRotation.Yaw);

}
