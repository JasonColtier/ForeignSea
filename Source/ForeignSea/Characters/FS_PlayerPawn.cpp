// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_PlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ForeignSea/Core/FS_PawnMovementComponent.h"
#include "ForeignSea/Core/FS_ShootingComponent.h"
#include "../../../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(FS_Log);


// Sets default values
AFS_PlayerPawn::AFS_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Création des components
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	MovementComponent = CreateDefaultSubobject<UFS_PawnMovementComponent>(TEXT("Pawn Movement Component"));
	ShootingComponent = CreateDefaultSubobject<UFS_ShootingComponent>(TEXT("Shooting Component"));
	
	//Le mesh en tant que root
	RootComponent = Mesh;

	//Attachement des components
	SpringArmComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetupAttachment(RootComponent);
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
}

// Called to bind functionality to input
void AFS_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&AFS_PlayerPawn::MoveForward);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&AFS_PlayerPawn::Fire);

}

void AFS_PlayerPawn::MoveForward(float Value)
{
	if(Value != 0.f)
	{
		//on ajoute le mouvement 
		AddMovementInput(GetActorForwardVector(),Value,true);
	}
}

void AFS_PlayerPawn::Fire()
{
	ShootingComponent->Fire();
}

