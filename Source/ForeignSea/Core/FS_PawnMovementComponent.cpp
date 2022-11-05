// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_PawnMovementComponent.h"

#include "JCOCheatManager.h"
#include "LogTool.h"
#include "VectorTypes.h"
#include "ForeignSea/Characters/FS_GenericPawn.h"
#include "ForeignSea/Watermanager/FS_WaterManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UFS_PawnMovementComponent::UFS_PawnMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

float UFS_PawnMovementComponent::GetRotationSpeed()
{
	return RotationSpeed;
}


// Called when the game starts
void UFS_PawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	SetJcoGameInstance;

	Pawn = Cast<AFS_GenericPawn>(GetOwner());
	Controller = Cast<APlayerController>(Pawn->GetController());
	GetOwner()->OnActorHit.AddDynamic(this, &UFS_PawnMovementComponent::OnHit);

	WaterManager = Cast<AFS_WaterManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AFS_WaterManager::StaticClass()));
	if(!WaterManager)
		TRACE_ERROR("water manager not found !")
}


// Called every frame
void UFS_PawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveActor(DeltaTime);
	RotateActor(DeltaTime);
}

void UFS_PawnMovementComponent::MoveActor(float DeltaTime)
{
	/*
	 * Déplacement du personnage
	 */
	if (CorrectionDisplacement != FVector::Zero())
	{
		Pawn->SetActorLocation(Pawn->GetActorLocation() + CorrectionDisplacement, true);
		CorrectionDisplacement = FVector::Zero();
	}
	

	//on récupère le mouvement du pawn stocké à cette frame
	auto Direction = Pawn->ConsumeMovementInputVector();
	Direction *= FVector(1, 1, 0);

	if (Direction != FVector::Zero())
	{
		//le classique Direction * vitesse * deltatime
		const FVector Displacement = Direction * Acceleration * DeltaTime;

		//on accumule la vitesse dans le temps
		AccumulatedDisplacement += Displacement;

		//on clamp cette vitesse à la vitesse max (multipliée aussi par le deltatime !)
		AccumulatedDisplacement = AccumulatedDisplacement.GetClampedToSize(0, MaxMoveSpeed * DeltaTime);
	}

	FVector offsetWave = FVector::Zero();

	if(WaterManager)
	{
		float targetLevel = WaterManager->GetZoffsetWaterForActor(GetOwner());
		offsetWave.Z = targetLevel - GetOwner()->GetActorLocation().Z;
		TRACE_SCREEN(0,"offsetWave.Z %f",offsetWave.Z);
	}
	
	//on set la position du pawn
	Pawn->SetActorLocation(Pawn->GetActorLocation() + AccumulatedDisplacement + offsetWave, true);

	//le slow correspond à a résistance qui sera appliquéee
	float SlowDisplacement = 1 - (DeltaTime + Drag);

	//clamp de la valeur entre 0 et 1 pour en faire un coéficient
	SlowDisplacement = UKismetMathLibrary::FClamp(SlowDisplacement, 0.f, 1.f);

	//réduction de la vitesse grâce à ce coéficient inférieur à 1
	AccumulatedDisplacement *= SlowDisplacement;

	// TRACE("Displacement : %s",*AccumulatedDisplacement.ToString())
	// Debug{
	// 	DrawDebugDirectionalArrow(GetWorld(),GetOwner()->GetActorLocation(),GetOwner()->GetActorLocation() + AccumulatedDisplacement*100,100,FColor::Red);
	// }
}


void UFS_PawnMovementComponent::RotateActor(float DeltaTime)
{
	if (DisableAutoRotation)
		return;

	DrawDebugSphere(GetWorld(), Pawn->LocationToRotateToward, 30, 15, FColor::Blue);
	FRotator PawnRot = UKismetMathLibrary::FindLookAtRotation(Pawn->GetActorLocation(), Pawn->LocationToRotateToward);
	FRotator SmoothedRot = UKismetMathLibrary::RLerp(Pawn->GetActorRotation(), FRotator(0, PawnRot.Yaw, 0), RotationSpeed * DeltaTime, true);
	Pawn->SetActorRotation(SmoothedRot);
}

void UFS_PawnMovementComponent::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& HitInitialImpact)
{
	//Le reflection vector est égale à
	//r=d−2(d.n)n
	//where d.n is the dot product, and n must be normalized.
	//https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
	FVector reflectionDisplacement = (AccumulatedDisplacement - 2 * (UE::Geometry::Dot(AccumulatedDisplacement, HitInitialImpact.ImpactNormal)) * HitInitialImpact.ImpactNormal);
	CorrectionDisplacement = reflectionDisplacement;

	Debug 
	{
		const int DrawVectorLength = 20;

		//le vecteur direction à partir du point
		FVector lineTraceStart = HitInitialImpact.ImpactPoint;
		FVector lineTraceEnd = HitInitialImpact.ImpactPoint + AccumulatedDisplacement * DrawVectorLength;
		DrawDebugDirectionalArrow(GetWorld(), lineTraceStart, lineTraceEnd, 100, FColor::White);

		//le vecteur direction arrivant au point d'impact
		FVector initialDeplacementStart = HitInitialImpact.ImpactPoint - AccumulatedDisplacement * DrawVectorLength;
		FVector initialDeplacementEnd = HitInitialImpact.ImpactPoint;
		DrawDebugDirectionalArrow(GetWorld(), initialDeplacementStart, initialDeplacementEnd, 100, FColor::Cyan);

		//le vecteur réfléchit
		FVector reflectedVectorStart = HitInitialImpact.ImpactPoint;
		FVector reflectedVectorEnd = HitInitialImpact.ImpactPoint + reflectionDisplacement * DrawVectorLength;
		DrawDebugDirectionalArrow(GetWorld(), reflectedVectorStart, reflectedVectorEnd, 100, FColor::Red);
	}
}
