// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;

	TimeToNextCameraChange -= DeltaTime;
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		APlayerController* ourPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (ourPlayerController)
		{
			if (ourPlayerController->GetViewTarget() != cameraOne && cameraOne != nullptr)
			{
				ourPlayerController->SetViewTarget(cameraOne); // 즉시 카메라 1으로 이동
			}
			else
			{
				ourPlayerController->SetViewTargetWithBlend(cameraTwo, SmoothBlendTime);
			}
		}
	}
}

