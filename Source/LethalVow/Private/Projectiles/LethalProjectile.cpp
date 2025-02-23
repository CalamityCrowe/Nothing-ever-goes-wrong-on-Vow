// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/LethalProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"


// Sets default values
ALethalProjectile::ALethalProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));


	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = Collider;

	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(Collider);

	Collider->OnComponentHit.AddDynamic(this, &ALethalProjectile::OnHit);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ALethalProjectile::OnOverlap);
}

// Called when the game starts or when spawned
void ALethalProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALethalProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALethalProjectile::SetInUse(bool newUse)
{
	bInUse = newUse;
	SetActorEnableCollision(bInUse);
	SetActorHiddenInGame(!bInUse);
	SetActorTickEnabled(bInUse);
	GetWorldTimerManager().ClearTimer(TimerHandle);
	if (bInUse)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALethalProjectile::ReturnToPool, TimeToLive, false);
	}
}

void ALethalProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	SetInUse(false);
}

void ALethalProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetInUse(false);
}

void ALethalProjectile::ReturnToPool()
{
	SetInUse(false);
}

