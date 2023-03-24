// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FS_GenericPawn.generated.h"

class UFS_PawnMovementComponent;
class UCapsuleComponent;
class UFS_ShootingComponent;
class UFS_LifeComponent;
UCLASS()
class FOREIGNSEA_API AFS_GenericPawn : public APawn
{
	GENERATED_BODY()


	
public:
	// Sets default values for this pawn's properties
	AFS_GenericPawn();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(EditAnywhere)
	UFS_ShootingComponent* ShootingComponent;

	UPROPERTY(EditAnywhere)
	UFS_LifeComponent* LifeComponent;

	// UPROPERTY(EditAnywhere)
	// UFS_PawnMovementComponent* MovementComponent;

	//la position vers laquelle le pawn va se tourner grâce au mouvement component
	//les enfants pourront écrire cette valeur
	UPROPERTY()
	FVector LocationToRotateToward;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
