// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_MovementComponent.h"
#include "../Tools/LogTool.h"

// Sets default values for this component's properties
UFS_MovementComponent::UFS_MovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFS_MovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Pawn = Cast<APawn>(GetOwner());
}


// Called every frame
void UFS_MovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//on récupère le mouvement du pawn stocké à cette frame
	const auto Movement = Pawn->ConsumeMovementInputVector();

	//le classique * vitesse * deltatime
	const FVector Displacement = Movement * MovementSpeed * DeltaTime;

	//on applique le déplacement
	Pawn->SetActorLocation(Pawn->GetActorLocation() + Displacement, true);

	if (Movement != FVector::ZeroVector)
		TRACE("movement %s", *Movement.ToString());
}
