// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_EnemyPawn.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFS_EnemyPawn::AFS_EnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFS_EnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFS_EnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), 1, true);
	
	if (IsValid(Target))
	{
		RotateEnemyTowardTarget();
	}
}

// Called to bind functionality to input
void AFS_EnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFS_EnemyPawn::RotateEnemyTowardTarget()
{
	FVector centerToSurface = GetActorLocation();
	UKismetMathLibrary::Vector_Normalize(centerToSurface);

	FVector actorToTarget = UGameplayStatics::GetPlayerPawn(this,0)->GetActorLocation() - GetActorLocation();
	UKismetMathLibrary::Vector_Normalize(actorToTarget);

		
	FRotator rotTowardTarget = UKismetMathLibrary::MakeRotFromZX(centerToSurface,actorToTarget);
		
	SetActorRelativeRotation(rotTowardTarget);
}
