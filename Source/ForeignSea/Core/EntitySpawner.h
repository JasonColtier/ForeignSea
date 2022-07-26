// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ForeignSea/Characters/FS_EnemyPawn.h"
#include "GameFramework/Actor.h"
#include "EntitySpawner.generated.h"

class AFS_EnemyPawn;
UCLASS()
class FOREIGNSEA_API AEntitySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEntitySpawner();

	UPROPERTY(EditAnywhere)
	float SpawnRadius = 10;

	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFS_EnemyPawn> EnemySpawnedClass = AFS_EnemyPawn::StaticClass();

	UFUNCTION(BlueprintCallable)
	AFS_EnemyPawn* SpawnEnemyAroundPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
