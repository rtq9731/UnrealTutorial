// Fill out your copyright notice in the Description page of Project Settings.


#include "TextManagerActor.h"

// Sets default values
ATextManagerActor::ATextManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void ATextManagerActor::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(MainCam);

	StateTextRenderer->SetText("Ready!");
	MsgTextRenderer->SetText("Prees Space to Start");

	AnimInst = Cast<UCustomAnimInstance>(AnimInstMesh->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance());
}

// Called every frame
void ATextManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATextManagerActor::SetUpStartUI()
{
	AttackTextRenderer->SetVisibility(false);
}

void ATextManagerActor::SetUpGameUI(float timer)
{
	AttackTextRenderer->SetVisibility(true);
	MsgTextRenderer->SetText(FString::SanitizeFloat(FMath::Max(timer, 0.0f)));
}

void ATextManagerActor::SetStateText(FString str)
{
	StateTextRenderer->SetText(str);
}

void ATextManagerActor::SetAttackText(FString str)
{
	AttackTextRenderer->SetText(str);
}

void ATextManagerActor::SetMsgText(FString str)
{
	MsgTextRenderer->SetText(str);
}

void ATextManagerActor::SetbIsAttack(bool value)
{
	AnimInst->bIsAttack = value;
}

void ATextManagerActor::SetbIsFailed(bool value)
{
	AnimInst->bIsFailed = value;
}
