// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_GenericPawn.h"

#include "Components/CapsuleComponent.h"
#include "ForeignSea/Core/FS_LifeComponent.h"
#include "ForeignSea/Core/FS_PawnMovementComponent.h"
#include "ForeignSea/Core/FS_ShootingComponent.h"
#include "ForeignSea/Core/FS_SphericalMovementComp.h"

// Sets default values
AFS_GenericPawn::AFS_GenericPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	LifeComponent = CreateDefaultSubobject<UFS_LifeComponent>(TEXT("Life Component"));
	ShootingComponent = CreateDefaultSubobject<UFS_ShootingComponent>(TEXT("Shooting Component"));
	SphericalMovementComp = CreateDefaultSubobject<UFS_SphericalMovementComp>(TEXT("Spherical Movement Component"));

	//Le mesh en tant que root
	RootComponent = Mesh;
	CapsuleComponent->SetupAttachment(RootComponent);
	ShootingComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFS_GenericPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFS_GenericPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFS_GenericPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

