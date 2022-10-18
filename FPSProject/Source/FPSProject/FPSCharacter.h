// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	// 키를 누르면 점프 플래그 발생
	UFUNCTION()
		void StartJump();

	// 키를 놓으면 점프 플래그 삭제
	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void FIre(); // 발사 입력 처리

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = mesh)
		USkeletalMeshComponent* FPSMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;
};
