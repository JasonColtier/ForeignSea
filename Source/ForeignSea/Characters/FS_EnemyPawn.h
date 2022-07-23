// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FS_GenericPawn.h"
#include "FS_EnemyPawn.generated.h"

UCLASS()
class FOREIGNSEA_API AFS_EnemyPawn : public AFS_GenericPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFS_EnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
