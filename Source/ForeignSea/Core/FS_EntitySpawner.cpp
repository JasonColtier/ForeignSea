// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_EntitySpawner.h"

#include "JCOCheatManager.h"
#include "LogTool.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFS_EntitySpawner::AFS_EntitySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AFS_EnemyPawn* AFS_EntitySpawner::SpawnEnemyAroundPlayer()
{
	if(!IsValid(PlayerPawn))
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	if(!IsValid(PlayerPawn))
		return nullptr;

	FVector spawnCoo = UKismetMathLibrary::RandomUnitVector() *	SphereOnWorld->GetActorScale().X / 2 * 100;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AFS_EnemyPawn* Enemy = GetWorld()->SpawnActor<AFS_EnemyPawn>(EnemySpawnedClass,spawnCoo,FRotator::ZeroRotator,SpawnParameters);
	Enemy->Target = PlayerPawn;
	
	Debug{
		DrawDebugSphere(GetWorld(),spawnCoo,10,10,FColor::Red,true);
		TRACE_SCREEN(1,"spawned new enemy ! %s",*Enemy->GetName())
	}
	
	return Enemy;
}

// Called when the game starts or when spawned
void AFS_EntitySpawner::BeginPlay()
{
	Super::BeginPlay();

	SetJcoGameInstance;
}

// Called every frame
void AFS_EntitySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimerSpawnDelay+= DeltaTime;
	
	if(TimerSpawnDelay > SpawnDelay)
	{
		TimerSpawnDelay = 0;
		SpawnEnemyAroundPlayer();
	}
}

