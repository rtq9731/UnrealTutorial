// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomAnimInstance.h"
#include <Components/TextRenderComponent.h>
#include <Kismet/GameplayStatics.h>
#include "TextManagerActor.generated.h"

UCLASS()
class MINIGAME_API ATextManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATextManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UCustomAnimInstance* AnimInst;

	UPROPERTY(EditAnywhere) AActor* AnimInstMesh;
	UPROPERTY(EditAnywhere) AActor* MainCam;

	UPROPERTY(EditAnywhere) UTextRenderComponent* StateTextRenderer;
	UPROPERTY(EditAnywhere) UTextRenderComponent* MsgTextRenderer;
	UPROPERTY(EditAnywhere) UTextRenderComponent* AttackTextRenderer;
	UPROPERTY(EditAnywhere) UTextRenderComponent* InfoTextRenderer;

public:
	void InitUI();
	void SetFinishedUI(int dealCounter, int maxDealCounter);
	void SetUpGameUI(float timer);
	void UpdateGameUI(float timer);
	void UpdateGameUI(float timer, FString key);

	void SetbIsAttack(bool value);
	void SetbIsFailed(bool value);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
