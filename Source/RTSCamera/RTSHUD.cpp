// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSHUD.h"



ARTSHUD::ARTSHUD() {
	DrawEdgeCollision((1.0/6.0), 0.1);
}

void ARTSHUD::DrawEdgeCollision(float HeightRatio, float WidthRatio) {
	const FVector2D & ViewportSize = FVector2D(1,1);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/ViewportSize);
	}

	float X = ViewportSize->X;
	float Y = ViewportSize->Y;

	FVector2D LRSize = FVector2D(X * WidthRatio, Y);
	FVector2D TBSize = FVector2D(X, Y * HeightRatio);

	this->AddHitBox(FVector2D(0, 0), LRSize, FName("LeftHitBox"), false, 1);
	this->AddHitBox(FVector2D(0, 0), TBSize, FName("TopHitBox"), false, 1);

	this->AddHitBox(FVector2D((1 - WidthRatio) * X, 0), LRSize, FName("RightHitBox"), false, 1);
	this->AddHitBox(FVector2D(0, (1-HeightRatio) * Y), TBSize, FName("BottomHitBox"), false, 1);

}

void ARTSHUD::BeginPlay() {
	Super::BeginPlay();
}

void ARTSHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

FVector2D GetGameViewportSize()
{
	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	return Result;
}