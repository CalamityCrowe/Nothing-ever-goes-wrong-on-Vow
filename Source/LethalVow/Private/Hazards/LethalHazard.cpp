// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazards/LethalHazard.h"
#include "Components/CapsuleComponent.h"
// Sets default values
ALethalHazard::ALethalHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

}

// Called when the game starts or when spawned
void ALethalHazard::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALethalHazard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with %s"), *OtherActor->GetName());
}

void ALethalHazard::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End Overlap with %s"), *OtherActor->GetName());
}

