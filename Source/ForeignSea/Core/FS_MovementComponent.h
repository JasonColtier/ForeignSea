// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FS_MovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOREIGNSEA_API UFS_MovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFS_MovementComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	APawn* Pawn;

	UPROPERTY()
	APlayerController* Controller;

	UPROPERTY()
	FVector AccumulatedDisplacement;

	UPROPERTY(EditAnywhere)
	float Acceleration = 1000.0f;

	//max movement speed
	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed = 10.f;
	

	/**
	 * @brief chaque frame on retire X % de la vitesse
	 */
	UPROPERTY(EditAnywhere)
	float Drag = 0.95f;

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
