// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDown.h"

// Sets default values
ACountDown::ACountDown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownComponent"));
	TextRenderer->SetHorizontalAlignment(EHTA_Center);
	TextRenderer->SetWorldSize(150.0f);
	
	RootComponent = TextRenderer;

	CountDownTime = 3.0f;

}

// Called when the game starts or when spawned
void ACountDown::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACountDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACountDown::UpdateTimerDisplay()
{
	TextRenderer->
}

