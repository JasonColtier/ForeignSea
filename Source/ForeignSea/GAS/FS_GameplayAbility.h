// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FS_GameplayAbility.generated.h"

/**
 * 
 */

UENUM()
enum EActivationPolicy
{
	HeldInput,
	Click
};

UCLASS()
class FOREIGNSEA_API UFS_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	
	
public:
	UPROPERTY(EditAnywhere,Category="ForeignSea")
	TEnumAsByte<EActivationPolicy> ActivationPolicy;
};
