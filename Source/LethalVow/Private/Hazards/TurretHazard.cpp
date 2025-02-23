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
	

	TraceDistance = 1000.0f;
}

void ATurretHazard::BeginPlay()
{
	Super::BeginPlay();
	TurretLightComponent->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepWorldTransform,FName());

	CurrentRotation = TurretMesh->GetSocketRotation(SocketName);
	UE_LOG(LogTemp, Warning, TEXT("Yaw at Begin: %f"), CurrentRotation.Yaw);
	GetWorld()->GetTimerManager().SetTimer(RotateHandle, this, &ATurretHazard::RotateTurret, 0.05f, true);
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
	FVector EndPos = StartPos + (TurretLightComponent->GetForwardVector() * TraceDistance);

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
		CurrentRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), TurnRate);
		TurretMesh->GetSocketTransform(SocketName).SetRotation(CurrentRotation.Quaternion());
		//TurretLightComponent->SetWorldRotation(GetMesh()->GetComponentRotation());
		//TurretLightComponent->SetLightColor(AttackLightColor);
		//TurretLightComponent
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Yaw at Handle: %f"), CurrentRotation.Yaw);
		if (GetWorld()->GetTimerManager().IsTimerActive(ToggleHandle) == false)
		{

			if (bRotateClockwise)
			{
				CurrentRotation.Yaw = FMath::Clamp(CurrentRotation.Yaw + (GetWorld()->GetDeltaSeconds() * TurnRate), MinRotation.Yaw, MaxRotation.Yaw);
			}
			else
			{
				CurrentRotation.Yaw = FMath::Clamp(CurrentRotation.Yaw - (GetWorld()->GetDeltaSeconds() * TurnRate), MinRotation.Yaw, MaxRotation.Yaw);
				//bRotateClockwise = true;
			}
		}
		if (((CurrentRotation.Yaw <= MinRotation.Yaw) || (CurrentRotation.Yaw >= MaxRotation.Yaw)) && (GetWorld()->GetTimerManager().IsTimerActive(ToggleHandle) == false))
		{
			GetWorld()->GetTimerManager().SetTimer(ToggleHandle, this, &ATurretHazard::FlipRotation, 3.0f, false);
		}
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("Current Rotation: %f"), CurrentRotation.Yaw));
		TurretMesh->GetSocketTransform(SocketName).SetRotation(CurrentRotation.Quaternion());
		//TurretLightComponent->SetWorldRotation(GetMesh()->GetComponentRotation());
	}
}
