// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_PlayerPawn.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "LogTool.h"
#include "ForeignSea/Core/FS_PawnMovementComponent.h"
#include "ForeignSea/GAS/FS_AbilitySystemComponent.h"
#include "ForeignSea/GAS/FS_GameplayAbility.h"
#include "ForeignSea/Inputs/FS_InputComponent.h"
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
	FS_AbilitySystemComponent = CreateDefaultSubobject<UFS_AbilitySystemComponent>(TEXT("Ability System Component"));
	AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("Attribute set"));

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

	UEnhancedInputLocalPlayerSubsystem* InputSystem = Cast<APlayerController>(GetController())->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	InputSystem->AddMappingContext(MappingContext,0);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AFS_PlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("Rotate", this, &AFS_PlayerPawn::Rotate);
	
	FS_InputComponent = Cast<UFS_InputComponent>(PlayerInputComponent);
	FS_InputComponent->BindAbility(FS_AbilitySystemComponent,&UFS_AbilitySystemComponent::Input_AbilityInputTagPressed,&UFS_AbilitySystemComponent::Input_AbilityInputTagReleased,FS_AbilitySystemComponent->InputBindings);
}

void AFS_PlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<APlayerController>(NewController);
	FS_AbilitySystemComponent->InitAbilityActorInfo(NewController,this);
}

UAbilitySystemComponent* AFS_PlayerPawn::GetAbilitySystemComponent() const
{
	return FS_AbilitySystemComponent;
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
	AddActorLocalRotation(FRotator(0,	Value*TurnSpeed*GetWorld()->DeltaTimeSeconds,0));
}
