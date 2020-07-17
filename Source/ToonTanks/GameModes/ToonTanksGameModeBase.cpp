// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"

AToonTanksGameModeBase::AToonTanksGameModeBase()
{

}


void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AToonTanksGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToonTanksGameModeBase::ActorDied(AActor * deadActor)
{
}

void AToonTanksGameModeBase::HandleGameStart() 
{
}

void AToonTanksGameModeBase::HandleGameOver(bool playerWon)
{
}