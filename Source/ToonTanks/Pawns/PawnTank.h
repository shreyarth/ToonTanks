// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* tankCam;

	FVector moveDirection;
	FQuat rotDirection;
	APlayerController* playerControllerRef;
	FHitResult traceHitResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed var", meta = (AllowPrivateAccess = "true"))
		float moveSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed var", meta = (AllowPrivateAccess = "true"))
		float rotSpeed = 100.f;

	bool bIsPlayerAlive = true;


	void CalculateMoveInput(float value);
	void CalculateRotInput(float value);

	void Move();
	void Rotate();

public:
	// Sets default values for this pawn's properties
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
