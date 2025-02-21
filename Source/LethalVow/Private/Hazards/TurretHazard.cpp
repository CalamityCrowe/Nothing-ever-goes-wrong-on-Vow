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

	SpotLightCollision->OnComponentBeginOverlap.AddDynamic(this, &ATurretHazard::BeginOverlap);

	TraceDistance = 1000.0f;
}

void ATurretHazard::BeginPlay()
{
	Super::BeginPlay(); 
}

FHitResult ATurretHazard::SearchForPlayer()
{
	FVector StartPos = GetActorLocation();
	FVector EndPos = StartPos + (GetActorForwardVector() * TraceDistance);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Hit, StartPos, EndPos, ECC_Visibility, QueryParams);
	return Hit;
}

void ATurretHazard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BeginOverlap"));
	if(ALethalPlayer* TempPlayer = Cast<ALethalPlayer>(OtherActor))
	{
		if (TempPlayer->IsAlive())
		{
			PlayerRef = TempPlayer;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurretHazard::RotateTurret,0.1f, true);
		}
	}
}

void ATurretHazard::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ALethalPlayer* TempPlayer = Cast<ALethalPlayer>(OtherActor))
	{
		if (TempPlayer == PlayerRef)
		{
			PlayerRef = nullptr;
			GetWorldTimerManager().ClearTimer(TimerHandle);
		}
	}
}

void ATurretHazard::RotateTurret()
{
	if (SearchForPlayer().GetActor() == PlayerRef)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerRef->GetActorLocation());
		FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), TurnRate);
		GetMesh()->SetWorldRotation(CurrentRotation);
	}
}
