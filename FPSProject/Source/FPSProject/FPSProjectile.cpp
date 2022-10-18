// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 구체 모양 콜리전 사용
	CollisionCompnent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCompoent"));
	// 구체 충돌 반경 설정
	CollisionCompnent->InitSphereRadius(15.0f);
	// 루트 컴포넌트를 충돌 컴포넌트로 설정
	RootComponent = CollisionCompnent;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

