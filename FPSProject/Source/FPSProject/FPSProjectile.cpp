// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 구체 모양 콜리전 사용
	CollisionCompnent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCompoent"));
	// 콜리전의 프로피를 Projectile로 설정
	CollisionCompnent->SetCollisionProfileName(TEXT("Projectile"));
	// 구체 충돌 반경 설정
	CollisionCompnent->InitSphereRadius(15.0f);
	// 구체 충돌시 발생할 함수를 지정한다.
	CollisionCompnent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
	// 루트 컴포넌트를 충돌 컴포넌트로 설정
	RootComponent = CollisionCompnent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionCompnent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	// 오브젝트의 생존 시간을 3초로 만듭니다.
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSProjectile::FireInDirection(const FVector& ShootDir)
{
	ProjectileMovementComponent->Velocity = ShootDir * ProjectileMovementComponent->InitialSpeed;
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}

