// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedActionKeyMapping.h"
#include "GameplayTagContainer.h"
#include "FCustomInputBindingToTag.generated.h"

/**
 * 
 */
USTRUCT()
struct FCustomInputBindingToTag
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag Tag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere)
	UInputAction* Input = nullptr;
};