// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "FPSProjectile.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());

	// 카메라 위치를 눈 살짝 위쪽으로 잡습니다.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// 폰의 카메라 로테이션 제어를 허용합니다.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 일인칭 메시 컴포넌트
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	// 소유 플레이어만 이 메시를 볼수 있도록
	FPSMesh->SetOnlyOwnerSee(true);
	// FPS 메시를 FPS 카메라에 붙입니다.
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSChar"));
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

	// 축에 함수를 바인딩한다.
	PlayerInputComponent->BindAxis("Vertical", this, &AFPSCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &AFPSCharacter::MoveHorizontal);

	PlayerInputComponent->BindAxis("MouseVertical", this, &AFPSCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MouseHorizontal", this, &AFPSCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveVertical(float Value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X); // X축 기준의 전방 ( Forward )을 알아온다.
	AddMovementInput(dir, Value);
}

void AFPSCharacter::MoveHorizontal(float Value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y); // Y축 기준의 전방 ( Right )을 알아온다.
	AddMovementInput(dir, Value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	// 프로젝타일 발사를 시도합니다.
	if (ProjectileClass)
	{
		// 카메라 트랜스폼을 구합니다.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// MuzzleOffset 을 카메라 스페이스에서 월드 스페이스로 변환합니다.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		// 조준선을 약간 윗쪽으로 조준합니다.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// 총구 위치에 발사체를 스폰시킵니다.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// 발사 방향을 알아냅니다.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireDirection(LaunchDirection);
			}
		}
	}
}
