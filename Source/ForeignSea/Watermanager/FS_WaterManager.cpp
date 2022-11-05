// Fill out your copyright notice in the Description page of Project Settings.


#include "ForeignSea/Watermanager/FS_WaterManager.h"

// Sets default values
AFS_WaterManager::AFS_WaterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFS_WaterManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFS_WaterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFS_WaterManager::GetZoffsetWaterForActor(AActor* Actor)
{
	if(MapOffsetByActor.Find(Actor))
	{
		return MapOffsetByActor[Actor];
	}else
	{
		MapOffsetByActor.Add(Actor);
		return 0;
	}
}

