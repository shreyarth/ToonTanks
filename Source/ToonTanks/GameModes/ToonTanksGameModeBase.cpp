// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

AToonTanksGameModeBase::AToonTanksGameModeBase()
{

}


void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}

void AToonTanksGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToonTanksGameModeBase::ActorDied(AActor * deadActor)
{
	//Check who died
	//If player...go to lose condition
	//If turret...decrease turret number
	UE_LOG(LogTemp, Warning, TEXT("A pawn has died"));
	if (deadActor == playerTank) {
		playerTank->HandleDestruction();
		HandleGameOver(false);

		if (playerControllerRef) {
			playerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* destroyedTurret = Cast<APawnTurret>(deadActor)) {
		destroyedTurret->HandleDestruction();

		if (--targetTurrets == 0) { HandleGameOver(true); }
	}
}

int32 AToonTanksGameModeBase::GetTargetTurrets()
{
	TArray<AActor*> turretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), turretActors);
	return turretActors.Num();
}

void AToonTanksGameModeBase::HandleGameStart()
{
	//Intialize game start, activate turrets, check if all pawns are active.
	//Start the blueprint version of GameStart()
	targetTurrets = GetTargetTurrets();
	playerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	playerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	GameStart();

	if (playerControllerRef) {
		playerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle playerEnableHandle;
		FTimerDelegate playerEnableDelegate = FTimerDelegate::CreateUObject(playerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(playerEnableHandle, playerEnableDelegate, startDelay, false);
	}
}

void AToonTanksGameModeBase::HandleGameOver(bool playerWon)
{
	//Check for the game win or lose conditions
	//If player is dead, show lost game
	//If player kills all turrets, show win game
	//Call blueprint version of GameOver(bool playerWon)
	GameOver(playerWon);
}