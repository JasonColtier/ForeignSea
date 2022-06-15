// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_MovementComponent.h"
#include "../Tools/LogTool.h"
#include "Kismet/KismetMathLibrary.h"

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
	Controller = Cast<APlayerController>(Pawn->GetController());
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

	// if (Movement != FVector::ZeroVector)
	// 	TRACE("movement %s", *Movement.ToString());

	FVector MouseLoc;
	FVector MouseDir;
	
	if(Controller->DeprojectMousePositionToWorld(MouseLoc,MouseDir))
	{
		FHitResult HitResult;
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams();
		bool HitSuccess = GetWorld()->LineTraceSingleByChannel(
			HitResult,		//result
			MouseLoc,		//start
			MouseLoc + MouseDir*5000,		//end
			ECC_Pawn,	//collision channel
			RV_TraceParams
			);

		if(HitSuccess)
		{
			DrawDebugSphere(GetWorld(),HitResult.Location,10,15,FColor::Blue);
			FRotator PawnRot = UKismetMathLibrary::FindLookAtRotation(Pawn->GetActorLocation(),HitResult.Location);
			Pawn->SetActorRotation(FRotator(0,PawnRot.Yaw,0));
		}else
		{
			TRACE_ERROR("mouse raycast did not hit !");
		}
	}else
	{
		TRACE_ERROR("not able to point find mouse position !");
	}
}
