// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_Projectile.h"

// Sets default values
AFS_Projectile::AFS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;
	
}

// Called when the game starts or when spawned
void AFS_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

