// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_SphericalMovementComp.h"

#include "LogTool.h"
#include "ForeignSea/Characters/FS_GenericPawn.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UFS_SphericalMovementComp::UFS_SphericalMovementComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFS_SphericalMovementComp::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<APawn>(GetOwner());
	
}


// Called every frame
void UFS_SphericalMovementComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto Direction = Pawn->ConsumeMovementInputVector();
	TRACE("direction %s",*Direction.ToString());

	// FVector newPos = UKismetMathLibrary::RotateAngleAxis(Pawn->GetActorLocation(),DeltaTime*-50,Pawn->GetActorRightVector());
	//
	// Pawn->SetActorLocation(newPos);
	//
	// FRotator newRot = UKismetMathLibrary::MakeRotFromXZ(Pawn->GetActorLocation(),Pawn->GetActorForwardVector());
	//
	// Pawn->SetActorRotation(UKismetMathLibrary::ComposeRotators(newRot,FRotator(0,0,90)));
	
}

