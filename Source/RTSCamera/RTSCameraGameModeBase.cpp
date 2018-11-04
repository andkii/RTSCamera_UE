// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSCameraGameModeBase.h"
#include "RTSPlayerController.h"
#include "RTSPawn.h"

// Sets default values
ARTSCameraGameModeBase::ARTSCameraGameModeBase()
{
	PlayerControllerClass = ARTSPlayerController::StaticClass();
	DefaultPawnClass = ARTSPawn::StaticClass();
}