// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FS_GenericPawn.h"
#include "JCOCheatManager.h"
#include "GameFramework/Pawn.h"
#include "JcoGameInstanceSubsystem.h"
#include "FS_PlayerPawn.generated.h"

class UFS_PawnMovementComponent;
class UFS_ShootingComponent;
class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class FOREIGNSEA_API AFS_PlayerPawn : public AFS_GenericPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFS_PlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	DeclareJcoDebug;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void Rotate(float Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//quand on est possessed
	virtual void PossessedBy(AController* NewController) override;
};




