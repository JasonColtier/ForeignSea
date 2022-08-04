// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "JcoGameInstanceSubsystem.generated.h"

class UJCOCheatManager;
/**
 * 
 */
UCLASS()
class JCO_UE5_PLUGIN_API UJcoGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UPROPERTY(VisibleAnywhere,Category = "JCO Debug")
	UJCOCheatManager* CheatManager;
};
