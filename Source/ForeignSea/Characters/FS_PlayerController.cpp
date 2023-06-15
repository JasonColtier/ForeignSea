// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_PlayerController.h"

#include "FS_PlayerPawn.h"
#include "ForeignSea/ForeignSeaGameModeBase.h"
#include "ForeignSea/GAS/FS_AbilitySystemComponent.h"


// Sets default values
AFS_PlayerController::AFS_PlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFS_PlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	// TRACE_SCREEN(0,"Process inputs !");

	if(IsValid(FS_Pawn) && IsValid(FS_Pawn->GetAbilitySystemComponent()))
	{
		AbilitySystemComponent->ProcessInput(DeltaTime,bGamePaused);
	}

}

void AFS_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	FS_Pawn = Cast<AFS_PlayerPawn>(GetPawn());
	if(FS_Pawn)
	{
		AbilitySystemComponent = Cast<UFS_AbilitySystemComponent>(FS_Pawn->GetAbilitySystemComponent());
	}
	
}

// Called every frame
void AFS_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

