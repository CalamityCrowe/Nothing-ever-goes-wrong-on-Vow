// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonMaster.generated.h"

class AMasterRoom;

UCLASS()
class LETHALVOW_API ADungeonMaster : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADungeonMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

#pragma region Variables
	TArray<USceneComponent*>Exits;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rooms", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AMasterRoom>> PossibleRooms;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rooms", meta = (AllowPrivateAccess = true))
	int RoomAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rooms", meta = (AllowPrivateAccess = true))
	TSubclassOf<AMasterRoom> StartRoom;

	TArray<UPrimitiveComponent*> OverlappedList;
	TObjectPtr<AMasterRoom> LatestRoom;


	USceneComponent* SelectedExit;

#pragma endregion

public:
	void SpawnStartRoom();
	void SpawnNextRoom();
	void AddOverlappingRoom();
	void CheckOverlap();
	void CloseHoles();

};
