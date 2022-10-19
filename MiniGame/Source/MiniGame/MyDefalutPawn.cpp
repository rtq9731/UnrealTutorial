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

	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATextManagerActor::StaticClass(), ActorsToFind);
	}

	for (AActor* FireEffectActor : ActorsToFind)
	{
		//이 액터의 유형이 ATextManagerActor 클래스인지 여부입니다.
		TextManager = Cast<ATextManagerActor>(FireEffectActor);
		if (TextManager)
		{
			TextManager->SetUpStartUI();
		}
	}

	TextManager->SetUpStartUI();

	DealTimer = DealTime;
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
	TextManager->SetMsgText(FString::SanitizeFloat(FMath::Max(DealTimer, 0.0f)));
	if (DealTimer <= 0.0f)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished();
	}
}

void AMyDefalutPawn::OnTimerFinished()
{
	bIsOnGame = false;
	TextManager->SetStateText(TEXT("Ready!"));
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

	TextManager->SetAttackText(CurKey);
}

void AMyDefalutPawn::CheckKey()
{
	if (!bIsOnGame)
		return;

	const bool bIsAttack = CurInputKey == CurKey;

	TextManager->SetbIsAttack(bIsAttack);
	TextManager->SetbIsAttack(!bIsAttack);
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
	TextManager->SetUpGameUI(0.0f);

	MakeRandAttackKey();
}

