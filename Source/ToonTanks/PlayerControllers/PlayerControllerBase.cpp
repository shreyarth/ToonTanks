// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"


void APlayerControllerBase::SetPlayerEnabledState(bool setPlayerEnabled) {
	if (setPlayerEnabled) {
		GetPawn()->EnableInput(this);
	}
	else {
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = setPlayerEnabled;
}