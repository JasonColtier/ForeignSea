// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JCOCheatManager.h"
#include "ForeignSea/Characters/FS_EnemyPawn.h"
#include "GameFramework/Actor.h"
#include "JcoGameInstanceSubsystem.h"
#include "FS_EntitySpawner.generated.h"

class AFS_EnemyPawn;
UCLASS()
class FOREIGNSEA_API AFS_EntitySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	DeclareJcoDebug;

	// Sets default values for this actor's properties
	AFS_EntitySpawner();

	//La distance à laquelle les enemis vont spawner du joueur
	UPROPERTY(EditAnywhere)
	int SpawnConeRadius = 70;

	//le pawn
	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	AActor* SphereOnWorld;

	/**
	 * @brief Le délai de spawn en secondes
	 */
	UPROPERTY(EditAnywhere)
	float SpawnDelay = 1;

	//les enemis spawnés
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFS_EnemyPawn> EnemySpawnedClass = AFS_EnemyPawn::StaticClass();

	//la fonction qui fait spawner un enemi au hasard !
	UFUNCTION(BlueprintCallable)
	AFS_EnemyPawn* SpawnEnemyAroundPlayer();

private:
	UPROPERTY()
	float TimerSpawnDelay = 0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
