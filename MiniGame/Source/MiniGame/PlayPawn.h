// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TextRenderComponent.h"
#include "CustomAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PlayPawn.generated.h"

UCLASS()
class MINIGAME_API APlayPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnClickRight();
	UFUNCTION()
		void OnClickLeft();
	UFUNCTION()
		void OnClickStart();
	UFUNCTION()
		void OnTimerTick();

	void OnTimerFinished();
	void CheckKey();
	void MakeRandAttackKey();

	UPROPERTY(EditAnywhere)
		int DealTime = 3;

	bool bIsOnGame = false;

	FString CurInputKey = "";
	FString CurKey = "";

	FTimerHandle TimerHandle;

	UCustomAnimInstance* AnimInst;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* StateTextRenderer;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MsgTextRenderer;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* AttackTextRenderer;

	UPROPERTY(EditAnywhere)
	AActor* MainCam;
};
