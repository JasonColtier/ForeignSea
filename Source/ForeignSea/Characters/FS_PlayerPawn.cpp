// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_PlayerPawn.h"

#include "AbilitySystemComponent.h"
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
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
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

	PlayerInputComponent->BindAxis("MoveForward", this, &AFS_PlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("Rotate", this, &AFS_PlayerPawn::Rotate);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, ShootingComponent, &UFS_ShootingComponent::StartFiring);
	PlayerInputComponent->BindAction("Fire", IE_Released, ShootingComponent, &UFS_ShootingComponent::StopFiring);

	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent,FGameplayAbilityInputBinds("ConfirmInput","CancelInput","GameplayAbilityInputs"));
}

void AFS_PlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<APlayerController>(NewController);
	AbilitySystemComponent->InitAbilityActorInfo(NewController,this);
}

UAbilitySystemComponent* AFS_PlayerPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFS_PlayerPawn::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{
	if(IsValid(AbilitySystemComponent) && IsValid(AbilityClass))
	{
		//create an object 
		UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();

		if(IsValid(Ability))
		{
			//struct for our ability
			FGameplayAbilitySpec AbilitySpec(
			Ability,
			Level,
			InputCode
			);

			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
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
