// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret() {

}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(fireRateTimer, this, &APawnTurret::CheckFireCondition, fireRate, true, false);

	player = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction(){
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!player || DistanceToPlayer() > fireRange) { return;  }
	RotateTurret(player->GetActorLocation());
}

void APawnTurret::CheckFireCondition() {
	//If player is dead, then return
	if (!player) { return; }

	if (DistanceToPlayer() <= fireRange) {
		//UE_LOG(LogTemp, Warning, TEXT("FIRE"));
		Fire();
	}
}

float APawnTurret::DistanceToPlayer() {
	//If player is dead, then return distance 0
	if (!player) { return 0.f; }

	float dist = (player->GetActorLocation() - GetActorLocation()).Size();
	return dist;
}