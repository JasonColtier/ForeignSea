// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JCOCheatManager.h"
#include "JcoGameInstanceSubsystem.h"
#include "FS_PawnMovementComponent.generated.h"


class AFS_GenericPawn;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOREIGNSEA_API UFS_PawnMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFS_PawnMovementComponent();

	float GetRotationSpeed();

	UPROPERTY()
	bool DisableAutoRotation = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	DeclareJcoDebug
	
	UPROPERTY(VisibleAnywhere)
	AFS_GenericPawn* Pawn;

	UPROPERTY()
	APlayerController* Controller;

	/**
	 * @brief permet de conserver la vitesse de déplacement dans le temps
	 */
	UPROPERTY()
	FVector AccumulatedDisplacement;

	UPROPERTY()
	FVector CorrectionDisplacement;

	/**
	 * @brief Acceleration du pawn
	 */
	UPROPERTY(EditAnywhere)
	float Acceleration = 50.0f;


	/**
	 * @brief Vitesse de mouvement maximum
	 */
	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed = 1000.f;
	

	/**
	 * @brief chaque frame on retire X % de la vitesse
	 */
	UPROPERTY(EditAnywhere)
	float Drag = 0.005f;

	/**
	 * @brief Vitesse de rotation
	 */
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 1.0f;
	
	/**
	 * @brief Déplace le pawn
	 * @param DeltaTime 
	 */
	UFUNCTION()
	void MoveActor(float DeltaTime);

	/**
	 * @brief Effectue la rotation du pawn
	 * @param DeltaTime 
	 */
	UFUNCTION()
	void RotateActor(float DeltaTime);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& HitInitialImpact);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};


