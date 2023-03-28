﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FS_SphericalMovementComp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOREIGNSEA_API UFS_SphericalMovementComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFS_SphericalMovementComp();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	APawn* Pawn;

private:
	UPROPERTY()
	float AccumulatedDisplacement =0;

	UPROPERTY(EditAnywhere)
	float Acceleration = 8;

	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed = 10;

	UPROPERTY(EditAnywhere)
	float Drag = 0.005f;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
