// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	void CheckFireCondition();
	float DistanceToPlayer();

	FTimerHandle fireRateTimer;
	APawnTank* player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Rate", meta = (AllowPrivateAccess = "true"))
		float fireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Rate", meta = (AllowPrivateAccess = "true"))
		float fireRange = 500.f;

public:
	// Sets default values for this pawn's properties
	APawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;
};
