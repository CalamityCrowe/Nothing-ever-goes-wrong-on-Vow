// Fill out your copyright notice in the Description page of Project Settings.


#include "LethalGameMode.h"
#include "LethalGameState.h"

ALethalGameMode::ALethalGameMode()
{
	GameStateClass = ALethalGameState::StaticClass();
}