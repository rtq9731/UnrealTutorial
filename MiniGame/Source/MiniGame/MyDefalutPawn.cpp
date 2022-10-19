// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDefalutPawn.h"

// Sets default values
AMyDefalutPawn::AMyDefalutPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyDefalutPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayPawn->SetUpStartUI();

	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(MainCam);
	UGameplayStatics::GetPlayerController(this, 0)->SetPawn(this);

	DealTimer = DealTime;

	AnimInst = Cast<UCustomAnimInstance>(AnimInstMesh->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance());
}

// Called every frame
void AMyDefalutPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyDefalutPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Left", IE_Pressed, this, &AMyDefalutPawn::OnClickLeft);
	InputComponent->BindAction("Right", IE_Pressed, this, &AMyDefalutPawn::OnClickRight);
	InputComponent->BindAction("Start", IE_Pressed, this, &AMyDefalutPawn::OnClickStart);
}

void AMyDefalutPawn::OnTimerTick()
{
	DealTimer -= 0.01f;
	PlayPawn->SetMsgText(FString::SanitizeFloat(FMath::Max(DealTimer, 0.0f)));
	if (DealTimer <= 0.0f)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished();
	}
}

void AMyDefalutPawn::OnTimerFinished()
{
	bIsOnGame = false;
	PlayPawn->SetStateText(TEXT("Ready!"));
	DealTimer = DealTime;
}


void AMyDefalutPawn::MakeRandAttackKey()
{
	if (rand() % 2 == 0)
	{
		CurKey = "A";
	}
	else
	{
		CurKey = "D";
	}

	PlayPawn->SetAttackText(CurKey);
}

void AMyDefalutPawn::CheckKey()
{
	if (!bIsOnGame)
		return;

	const bool bIsAttack = CurInputKey == CurKey;

	AnimInst->bIsAttack = bIsAttack;
	AnimInst->bIsFailed = !bIsAttack;

	if (bIsAttack)
	{

	}
}

void AMyDefalutPawn::OnClickRight()
{
	CurInputKey = "D";
	CheckKey();
}

void AMyDefalutPawn::OnClickLeft()
{
	CurInputKey = "A";
	CheckKey();
}

void AMyDefalutPawn::OnClickStart()
{
	if (bIsOnGame)
		return;

	bIsOnGame = true;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyDefalutPawn::OnTimerTick, 0.01f, true);

	AttackTextRenderer->SetVisibility(true);
	MsgTextRenderer->SetText(FString::SanitizeFloat(FMath::Max(DealTimer, 0.0f)));

	MakeRandAttackKey();
}

