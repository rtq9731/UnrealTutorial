// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 카메라를 생성해줍니다.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// 내 오브젝트에 카메라를 붙여줍니다
	FPSCameraComponent->SetupAttachment(RootComponent);
	// 카메라 위치를 눈 살짝 위쪽으로 잡습니다.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// 폰의 카메라 로테이션 제어를 허용합니다.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// FPS 메쉬 생성
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// 소유 플레이어만 이 메시를 볼 수 있게 합니다.
	FPSMesh->bOnlyOwnerSee = true;
	// FPS 카메라에 팔 메시를 붙여요
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// 그림자 일부를 꺼서 메시가 하나인것처럼 보여줍니다.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 내 몸을 숨겨야 이상하지 않음
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		// 5 초간 디버그 메시지를 표시합니다. (첫 인수인) -1 "Key" 값은 이 메시지를 업데이트 또는 새로고칠 필요가 없음을 나타냅니다.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 움직임 구성
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// 마우스 움직임 구성
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
	
	// 점프 구성
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	// 공격 구성
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::FIre);
}

void AFPSCharacter::MoveForward(float Value)
{
	FVector Dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Dir, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::FIre()
{

}

