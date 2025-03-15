// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedural/MasterRoom.h"
#include "Components/BoxComponent.h"
#include"Procedural/EndWall.h"
// Sets default values
AMasterRoom::AMasterRoom()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ExitsFolder = CreateDefaultSubobject<USceneComponent>(TEXT("Exits Folder"));
	ExitsFolder->SetupAttachment(GetRootComponent());
	MeshFolder = CreateDefaultSubobject<USceneComponent>(TEXT("Mesh Folder"));
	MeshFolder->SetupAttachment(GetRootComponent());
	OverlapFolder = CreateDefaultSubobject<USceneComponent>(TEXT("Overlap Folder"));
	OverlapFolder->SetupAttachment(GetRootComponent());

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetCollisionProfileName("RoomOverlap");
	OverlapBox->SetupAttachment(OverlapFolder);

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(MeshFolder);


}

// Called when the game starts or when spawned
void AMasterRoom::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMasterRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



