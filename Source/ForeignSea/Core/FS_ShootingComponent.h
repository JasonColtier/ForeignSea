// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FS_ShootingComponent.generated.h"

class AFS_GenericPawn;
class AFS_Projectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOREIGNSEA_API UFS_ShootingComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFS_ShootingComponent();

	//la fréquence de tir (plus petit = plus rapide)
	UPROPERTY(EditAnywhere)
	float ShootingSpeed = 0.3f;

	//la classe de bale utilisée
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFS_Projectile> ProjectyleClass;

	//ref au pawn
	UPROPERTY()
	AFS_GenericPawn* Pawn;

	//on commence à tier
	UFUNCTION()
	void StartFiring();

	//on arrête de tirer
	UFUNCTION()
	void StopFiring();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//pas encore utilisé
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<AFS_Projectile>> projectilesArray;

	//timer interne pour compter le temps
	UPROPERTY()
	float TimerShootDelay = 0;

	//si on demande à tirer ou pas
	UPROPERTY()
	bool PlayerWantToShoot = false;

	//si le délai avant le prochain shoot est dépassé ou pas
	UPROPERTY()
	bool CanShoot = true;

	//spawn du projectile
	UFUNCTION()
	void SpawnProjectile();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
