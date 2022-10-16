// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleMoveActor.h"

// Sets default values
ASimpleMoveActor::ASimpleMoveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleMoveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation();
	float deltaMoveAmount = (FMath::Sin(runningTime + DeltaTime) - FMath::Sin(runningTime));
	newLocation.X += deltaMoveAmount * moveSpeed;
	runningTime += DeltaTime;
	SetActorLocation(newLocation);
}

