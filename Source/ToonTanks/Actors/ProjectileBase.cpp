// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = projectileMesh;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement->InitialSpeed = projectileSpeed;
	projectileMovement->MaxSpeed = projectileSpeed;

	trailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	trailComponent->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	//Get a reference as to who spawned the actor
	AActor* projectileOwner = GetOwner();

	if (!projectileOwner) { return; }
	//if otheractor is not the projectileowner or the projectile itself and it exists, then do damage
	if (otherActor != NULL && otherActor != this && otherActor != projectileOwner) {
		UGameplayStatics::ApplyDamage(otherActor, damage, projectileOwner->GetInstigatorController(), this, damageType);
		UGameplayStatics::SpawnEmitterAtLocation(otherActor, hitParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(hitShake);
		Destroy();
	}
	//Add more effects code here when polishing the game
}
