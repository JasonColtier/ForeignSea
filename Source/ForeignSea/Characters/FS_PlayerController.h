// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FS_PlayerController.generated.h"

class UFS_AbilitySystemComponent;
class AFS_PlayerPawn;

UCLASS()
class FOREIGNSEA_API AFS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFS_PlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	AFS_PlayerPawn* FS_Pawn;

	UPROPERTY()
	UFS_AbilitySystemComponent* AbilitySystemComponent;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
