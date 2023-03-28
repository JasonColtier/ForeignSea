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
}

// Called every frame
void AFS_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		// TRACE("move forward value %f", Value);
	}
}

void AFS_PlayerPawn::Rotate(float Value)
{
	//ligne importante : on aligne le pawn sur la surface de la sphère
	//ça marche car la sphère est à 0 en origine
	FVector upNormalOnSphere = GetActorLocation().GetSafeNormal();
	FVector rotationAxis = GetActorForwardVector().GetSafeNormal();

	TRACE("up normal %s , rot axis %s",*upNormalOnSphere.ToString(),*rotationAxis.ToString());
	
	FRotator newRot = UKismetMathLibrary::MakeRotFromZX(upNormalOnSphere,rotationAxis);	
	SetActorRotation(newRot);
	
	AddActorLocalRotation(FRotator(0,	Value*TurnSpeed*GetWorld()->DeltaTimeSeconds,0));
}
