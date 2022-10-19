// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayPawn.h"
#include "MyDefalutPawn.generated.h"

UCLASS()
class MINIGAME_API AMyDefalutPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyDefalutPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CheckKey();
	void OnTimerFinished();
	void MakeRandAttackKey();

	UFUNCTION()
		void MyFunc();

	UFUNCTION()
		void OnClickRight();
	UFUNCTION()
		void OnClickLeft();
	UFUNCTION()
		void OnClickStart();

	UFUNCTION()
		void OnTimerTick();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		int DealTime = 3;

	float DealTimer = 0.0f;

	UPROPERTY(EditAnywhere)
		bool bIsOnGame = false;

	FString CurInputKey = "";
	FString CurKey = "";

	FTimerHandle TimerHandle;

	UCustomAnimInstance* AnimInst;

	UPROPERTY(EditAnywhere)
		AActor* AnimInstMesh;

	UPROPERTY(EditAnywhere)
		AActor* MainCam;

	UPROPERTY(EditAnywhere)
		APlayPawn* PlayPawn;
};
