// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayPawn.h"

// Sets default values
APlayPawn::APlayPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	TextRenderer->SetHorizontalAlignment(EHTA_Center);
	TextRenderer->SetWorldSize(150.0f);
}

// Called when the game starts or when spawned
void APlayPawn::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, 1, true);
}

// Called every frame
void APlayPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Left", IE_Pressed, this, &APlayPawn::OnClickLeft);
	InputComponent->BindAction("Right", IE_Pressed, this, &APlayPawn::OnClickRight);
}

void APlayPawn::OnClickRight()
{
	CurKey = "D";
	CheckKey();
}

void APlayPawn::OnClickLeft()
{
	CurKey = "A";
	CheckKey();
}

void APlayPawn::CheckKey()
{
	AnimInst->bIsAttack = true;
}

