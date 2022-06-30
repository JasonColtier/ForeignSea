// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FS_ShootingComponent.generated.h"

class AFS_Projectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOREIGNSEA_API UFS_ShootingComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFS_ShootingComponent();

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float Damages;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFS_Projectile> ProjectyleClass;
	
	UFUNCTION()
	void Fire();




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<AFS_Projectile>> projectilesArray;

	UFUNCTION()
	void SpawnProjectile();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
