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

	//we get the input from pawn
	
	if (Pawn->ConsumeMovementInputVector() != FVector::Zero())
	{
		// TRACE("diff !");
		//le classique Direction * vitesse * deltatime
		const float Displacement = Acceleration * DeltaTime;

		//on accumule la vitesse dans le temps
		AccumulatedDisplacement += Displacement;

		//on clamp cette vitesse à la vitesse max (multipliée aussi par le deltatime !)
		AccumulatedDisplacement = UKismetMathLibrary::FClamp(AccumulatedDisplacement,0,MaxMoveSpeed * DeltaTime);
	}

	// TRACE("acc displacement : %f",AccumulatedDisplacement)
	//we move the player along the surface by rtating it agound the origin with the right vector = we are allways on a 2D sphere
	auto newLoc = UKismetMathLibrary::RotateAngleAxis(Pawn->GetActorLocation(), AccumulatedDisplacement * DeltaTime, Pawn->GetActorRightVector());
	Pawn->SetActorLocation(newLoc);

	//le slow correspond à a résistance qui sera appliquéee
	float SlowDisplacement = 1 - (DeltaTime + Drag);

	//clamp de la valeur entre 0 et 1 pour en faire un coéficient
	SlowDisplacement = UKismetMathLibrary::FClamp(SlowDisplacement, 0.f, 1.f);

	//réduction de la vitesse grâce à ce coéficient inférieur à 1
	AccumulatedDisplacement *= SlowDisplacement;
}