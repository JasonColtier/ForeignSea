// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FS_LifeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOREIGNSEA_API UFS_LifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFS_LifeComponent();
	
	UPROPERTY(EditAnywhere)
	int MaxLife = 3;

	UPROPERTY()
	int LifeAmount = MaxLife;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	UFUNCTION()
	void OnOwnerTakeDamage(AActor* DamagedActor, float Damage,const UDamageType* DamageType,  AController* InstigatedBy, AActor* DamageCauser);
	
		
};
