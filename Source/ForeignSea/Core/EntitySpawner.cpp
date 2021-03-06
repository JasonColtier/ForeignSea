// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawner.h"

#include "../../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEntitySpawner::AEntitySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AFS_EnemyPawn* AEntitySpawner::SpawnEnemyAroundPlayer()
{
	if(!PlayerPawn)
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	float randomAngle = FMath::RandRange(0.f,2 * PI);
	float x = SpawnRadius * FMath::Sin(randomAngle);
	float y = SpawnRadius * FMath::Cos(randomAngle);
	FVector location = FVector(x,y,20);
	location += PlayerPawn->GetActorLocation();

	DrawDebugSphere(GetWorld(),location,10,10,FColor::Red,true);
	
	AFS_EnemyPawn* Enemy = GetWorld()->SpawnActor<AFS_EnemyPawn>(EnemySpawnedClass,location,FRotator::ZeroRotator);

	//
	// TRACE_SCREEN("spawned new enemy ! %s",*Enemy->GetName())
	return nullptr;
}

// Called when the game starts or when spawned
void AEntitySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntitySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

