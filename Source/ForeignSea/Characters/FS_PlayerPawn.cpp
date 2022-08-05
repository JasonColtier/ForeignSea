// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_PlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ForeignSea/Core/FS_ShootingComponent.h"
#include "LogTool.h"
#include "ForeignSea/Core/FS_PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFS_PlayerPawn::AFS_PlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Création des components
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	//Attachement des scene components
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
}


// Called when the game starts or when spawned
void AFS_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	SetJcoGameInstance;
	MovementComponent->DisableAutoRotation = true;
}

// Called every frame
void AFS_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateShootTarget();
}

// Called to bind functionality to input
void AFS_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFS_PlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("Rotate", this, &AFS_PlayerPawn::Rotate);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, ShootingComponent, &UFS_ShootingComponent::StartFiring);
	PlayerInputComponent->BindAction("Fire", IE_Released, ShootingComponent, &UFS_ShootingComponent::StopFiring);
}

void AFS_PlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<APlayerController>(NewController);
}

void AFS_PlayerPawn::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		//on ajoute le mouvement 
		AddMovementInput(GetActorForwardVector(), Value, true);
	}

}

void AFS_PlayerPawn::Rotate(float Value)
{
	if(Value== 0)
	{
		return;
	}

	FRotator newRot = FRotator(0,MovementComponent->GetRotationSpeed()*Value,0);
	AddActorLocalRotation(newRot);
}

void AFS_PlayerPawn::CalculateShootTarget()
{
	if (!PlayerController)
		return;

	FVector MouseLoc;
	FVector MouseDir;

	if (PlayerController->DeprojectMousePositionToWorld(MouseLoc, MouseDir))
	{
		FHitResult HitResult;
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams();
		bool HitSuccess = GetWorld()->LineTraceSingleByChannel(
			HitResult, //result
			MouseLoc, //start
			MouseLoc + MouseDir * 50000, //end
			ECC_Camera	, //collision channel
			RV_TraceParams
		);

		if (HitSuccess)
		{
			LocationToRotateToward = HitResult.Location;
			FRotator ShootingRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LocationToRotateToward);
			ShootingComponent->SetWorldRotation(ShootingRot);
			
			Debug{
				DrawDebugSphere(GetWorld(),LocationToRotateToward*FVector(1,1,0),10,10,FColor::White);
			}
			
		}
		else
		{
			TRACE_ERROR("mouse raycast did not hit !");
		}
	}
	else
	{
		// TRACE_ERROR("not able to point find mouse position !");
	}
}
