// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FS_WaterManager.generated.h"

UCLASS(BlueprintType,Blueprintable)
class FOREIGNSEA_API AFS_WaterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFS_WaterManager();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	TMap<AActor*,float> MapOffsetByActor;
	
private:


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetZoffsetWaterForActor(AActor* Actor);

};
