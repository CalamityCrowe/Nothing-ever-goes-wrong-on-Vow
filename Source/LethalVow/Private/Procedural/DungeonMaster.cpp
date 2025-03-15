// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedural/DungeonMaster.h"
#include "Procedural/MasterRoom.h"
#include "Components/BoxComponent.h"
// Sets default values
ADungeonMaster::ADungeonMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonMaster::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnStartRoom();

}

// Called every frame
void ADungeonMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonMaster::SpawnStartRoom()
{
	if(IsValid(StartRoom))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		LatestRoom = GetWorld()->SpawnActor<AMasterRoom>(StartRoom, GetActorTransform(), SpawnParams);
		TArray<USceneComponent*> Temp;
		LatestRoom->GetExitsFolder()->GetChildrenComponents(false, Temp);
		Exits.Append(Temp);
		UE_LOG(LogTemp, Warning, TEXT("Exits: %d"), Exits.Num());
		//LatestRoom->GetExitsFolder();
		SpawnNextRoom();

	}
}

void ADungeonMaster::SpawnNextRoom()
{
	SelectedExit = Exits[FMath::RandRange(0, Exits.Num() - 1)]; 

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (LatestRoom = GetWorld()->SpawnActor<AMasterRoom>(PossibleRooms[FMath::RandRange(0, PossibleRooms.Num() - 1)], SelectedExit->GetComponentTransform(), SpawnParams)) 
	{
		CheckOverlap();
	}

}

void ADungeonMaster::AddOverlappingRoom()
{
	TArray<USceneComponent*> Overlaps;
	LatestRoom->GetOverlapFolder()->GetChildrenComponents(false, Overlaps);
	for (USceneComponent* box : Overlaps)
	{
		if (UBoxComponent* OB = Cast<UBoxComponent>(box)) 
		{
			TArray<UPrimitiveComponent*> NewList;
			OB->GetOverlappingComponents(NewList);
			OverlappedList.Append(NewList); 
		}
		//box->OnComponentBeginOverlap.AddDynamic(this, &ADungeonMaster::CheckOverlap);
	}
}

void ADungeonMaster::CheckOverlap()
{
	AddOverlappingRoom(); 
	if (OverlappedList.IsEmpty() == false)
	{
		OverlappedList.Empty();
		LatestRoom->Destroy();
		SpawnNextRoom();
	}
	else 
	{
		OverlappedList.Empty();
		RoomAmount--;
		Exits.Remove(SelectedExit);
		TArray<USceneComponent*> NewExits;
		LatestRoom->GetExitsFolder()->GetChildrenComponents(false, NewExits);
		Exits.Append(NewExits);
		if(RoomAmount > 0)
		{
			SpawnNextRoom();
		}
		else
		{
			CloseHoles();
		}

	}
}

void ADungeonMaster::CloseHoles()
{
	for (USceneComponent* Exit : Exits) 
	{
		// this needs a class to spawn the end wall
		//GetWorld()->SpawnActor<AEndWall>(PossibleRooms, Exit->GetComponentTransform());
	}

}

