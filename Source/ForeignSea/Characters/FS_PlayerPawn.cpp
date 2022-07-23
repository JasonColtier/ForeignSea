// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_PlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ForeignSea/Core/FS_PawnMovementComponent.h"
#include "ForeignSea/Core/FS_ShootingComponent.h"
#include "../../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"
#include "ForeignSea/Core/FS_LifeComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(FS_Log);


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
}

// Called every frame
void AFS_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateTargetRotation();
}

// Called to bind functionality to input
void AFS_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&AFS_PlayerPawn::MoveForward);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,ShootingComponent,&UFS_ShootingComponent::StartFiring);
	PlayerInputComponent->BindAction("Fire",IE_Released,ShootingComponent,&UFS_ShootingComponent::StopFiring);

}

void AFS_PlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<APlayerController>(NewController);
}

void AFS_PlayerPawn::MoveForward(float Value)
{
	if(Value != 0.f)
	{
		//on ajoute le mouvement 
		AddMovementInput(GetActorForwardVector(),Value,true);
	}
}

void AFS_PlayerPawn::CalculateTargetRotation()
{
	FVector MouseLoc;
	FVector MouseDir;

	if (PlayerController->DeprojectMousePositionToWorld(MouseLoc, MouseDir))
	{
		FHitResult HitResult;
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams();
		bool HitSuccess = GetWorld()->LineTraceSingleByChannel(
			HitResult, //result
			MouseLoc, //start
			MouseLoc + MouseDir * 5000, //end
			ECC_Pawn, //collision channel
			RV_TraceParams
		);

		if (HitSuccess)
		{
			LocationToRotateToward = HitResult.Location;
		}
		else
		{
			TRACE_ERROR("mouse raycast did not hit !");
		}
	}
	else
	{
		TRACE_ERROR("not able to point find mouse position !");
	}
}


