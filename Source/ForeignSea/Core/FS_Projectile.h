// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FS_Projectile.generated.h"

class AFS_GenericPawn;
class UCapsuleComponent;
UCLASS()
class FOREIGNSEA_API AFS_Projectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFS_Projectile();
	
	/**
	 * @brief Mesh of this projectile
	 */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	/**
	 * @brief Pour les collisions :)
	 */
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	/**
	 * @brief Base speed of this projectile
	 */
	UPROPERTY(EditAnywhere)
	float BaseSpeed = 10;

	/**
	* @brief Base speed of this projectile
	*/
	UPROPERTY(EditAnywhere)
	float BaseDamage = 1;

	/**
	 * @brief Lifetime in seconds
	 */
	UPROPERTY(EditAnywhere)
	float LifeTime = 3;

	UFUNCTION(BlueprintImplementableEvent)
	void ApplyKnockback(AActor* otherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//pour chopper la durée en vie
	float TimeCounter = 0;
	
	/**
	 * @brief 
	 * @return the speed of the bullet
	 */
	float GetSpeed() const
	{
		return BaseSpeed;
	}

	//quand on rencontre qqc
	UFUNCTION()
	void OnBeginOverlap(AActor* SelfActor, AActor* OtherActor);
};
