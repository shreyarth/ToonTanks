// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanks/GameModes/ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	health = defaultHealth;
	gameModeRef = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor * damagedActor, float damage, const UDamageType * damageType, AController * instigatedBy, AActor * damageCauser)
{
	if (damage == 0 || health <= 0) { return; }
	health = FMath::Clamp(health - damage, 0.f, defaultHealth);
	if (health <= 0) {
		if (gameModeRef) {
			gameModeRef->ActorDied(GetOwner());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No valid game mode reference"));
		}
	}
}

