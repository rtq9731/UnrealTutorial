// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayPawn.h"

// Sets default values
APlayPawn::APlayPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StateTextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MainTextRenderer"));

	StateTextRenderer->SetHorizontalAlignment(EHTA_Center);
	StateTextRenderer->SetWorldSize(150.0f);

	MsgTextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MsgTextRenderer"));
	MsgTextRenderer->SetHorizontalAlignment(EHTA_Center);
	MsgTextRenderer->SetWorldSize(64.0f);

	AttackTextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("AttackTextRenderer"));
	AttackTextRenderer->SetHorizontalAlignment(EHTA_Center);
	AttackTextRenderer->SetWorldSize(128.0f);
	
}

// Called when the game starts or when spawned
void APlayPawn::BeginPlay()
{
	Super::BeginPlay();

	StateTextRenderer->SetText("Attack!!!");

	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(MainCam);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayPawn::OnTimerTick, 1.0f, true);
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
	CurInputKey = "D";
	CheckKey();
}

void APlayPawn::OnClickLeft()
{
	CurInputKey = "A";
	CheckKey();
}

void APlayPawn::OnClickStart()
{
	if(!bIsOnGame)
		bIsOnGame = true;
}

void APlayPawn::OnTimerTick()
{
}

void APlayPawn::OnTimerFinished()
{
}

void APlayPawn::CheckKey()
{
	if(CurInputKey == CurKey)
	AnimInst->bIsAttack = true;
}

