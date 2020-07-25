// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"


class APawnTurret;
class APawnTank;
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	int32 targetTurrets = 0.f;
	APawnTank* playerTank;
	APlayerControllerBase* playerControllerRef;

	//These funcitons will handle the c++ side of the game mode, keeping track
	//of what is currently happening in the game
	int32 GetTargetTurrets();
	void HandleGameStart();
	void HandleGameOver(bool playerWon);

public:
	// Sets default values for this actor's properties
	AToonTanksGameModeBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActorDied(AActor* deadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
		int32 startDelay = 3;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//These functions will call the data from the C++ functions and 
	//will handle the displaying of that data on screen
	UFUNCTION(BlueprintImplementableEvent)
		void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool playerWon);
};
