// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APawnTank::APawnTank()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	springArm->SetupAttachment(RootComponent);

	tankCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
	tankCam->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	playerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction(){
	Super::HandleDestruction();

	//Hide player...create new function for it
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	if (playerControllerRef) {
		playerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, traceHitResult);
		FVector hitLoc = traceHitResult.ImpactPoint;

		RotateTurret(hitLoc);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float value)
{
	moveDirection = FVector(value * moveSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);
}

void APawnTank::CalculateRotInput(float value)
{
	float rotAmount = value * rotSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator rotation = FRotator(0.f, rotAmount, 0.f);
	rotDirection = FQuat(rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(moveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(rotDirection, true);
}