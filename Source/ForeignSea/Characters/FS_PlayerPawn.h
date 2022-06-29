// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FS_PlayerPawn.generated.h"

class UFS_PawnMovementComponent;
class UFS_ShootingComponent;
class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class FOREIGNSEA_API AFS_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFS_PlayerPawn();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	UFS_PawnMovementComponent* MovementComponent;
	
	UPROPERTY(EditAnywhere)
	UFS_ShootingComponent* ShootingComponent;
	
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void Fire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
