// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSPawn.h"


// Sets default values
ARTSPawn::ARTSPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARTSPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->Update(DeltaTime);

}

void ARTSPawn::Update(float DeltaTime) {
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	{
		FRotator NewRotation = Camera->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -55.0f, -15.0f);
		Camera->SetWorldRotation(NewRotation);
	}

	{
		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values * 300 units per second
			MovementInput = MovementInput.GetSafeNormal() * 300.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void ARTSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForwardBack", this, &ARTSPawn::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveRightLeft", this, &ARTSPawn::MoveRightLeft);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ARTSPawn::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ARTSPawn::CameraYaw);
} 

//Input functions
void ARTSPawn::MoveForwardBack(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ARTSPawn::MoveRightLeft(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ARTSPawn::CameraPitch(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ARTSPawn::CameraYaw(float AxisValue)
{
	CameraInput.X = AxisValue;
}