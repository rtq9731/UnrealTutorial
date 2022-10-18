// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��ü ��� �ݸ��� ���
	CollisionCompnent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCompoent"));
	// �ݸ����� �����Ǹ� Projectile�� ����
	CollisionCompnent->SetCollisionProfileName(TEXT("Projectile"));
	// ��ü �浹 �ݰ� ����
	CollisionCompnent->InitSphereRadius(15.0f);
	// ��ü �浹�� �߻��� �Լ��� �����Ѵ�.
	CollisionCompnent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
	// ��Ʈ ������Ʈ�� �浹 ������Ʈ�� ����
	RootComponent = CollisionCompnent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionCompnent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	// ������Ʈ�� ���� �ð��� 3�ʷ� ����ϴ�.
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

