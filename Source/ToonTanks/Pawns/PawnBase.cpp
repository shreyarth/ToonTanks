// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = capsuleComponent;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	projectileSpawn->SetupAttachment(turretMesh);
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void APawnBase::RotateTurret(FVector target)
{
	//Rotate the turrets on both AI and player to face the target's direction
	FVector turretLoc = turretMesh->GetComponentLocation();
	FRotator turretRot = UKismetMathLibrary::FindLookAtRotation(turretLoc, FVector(target.X, target.Y, turretMesh->GetComponentLocation().Z));

	turretMesh->SetWorldRotation(turretRot);
}

void APawnBase::Fire()
{
	//Fire projectiles at given intervals, same for both AI and the player
	UE_LOG(LogTemp, Warning, TEXT("FIRE"));
	FVector projectileSpawnLoc = projectileSpawn->GetComponentLocation();
	FRotator projectileSpawnRot = projectileSpawn->GetComponentRotation();

	if (projectileClass) {
		AProjectileBase* tempProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectileClass, projectileSpawnLoc, projectileSpawnRot);
		tempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	//A bit complicated
	//Functionality for player...particles, sounds, quality of life implementations


	//Some other modifiers applicable to individual children
	//if player dies, tell gamemode that player has died and hide everything and stop receiving input


	//if turret dies, tell gamemode that turret has died and destroy turret
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

