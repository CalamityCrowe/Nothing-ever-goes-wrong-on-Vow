// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedural/EndWall.h"

// Sets default values
AEndWall::AEndWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEndWall::BeginPlay()
{
	Super::BeginPlay();
	
}



