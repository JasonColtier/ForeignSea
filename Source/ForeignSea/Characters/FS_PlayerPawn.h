// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "FS_GenericPawn.h"
#include "GameplayTagContainer.h"
#include "JCOCheatManager.h"
#include "JcoGameInstanceSubsystem.h"
#include "FS_PlayerPawn.generated.h"

class UFS_AbilitySystemComponent;
class UGameplayAbility;
class UFS_PawnMovementComponent;
class UFS_ShootingComponent;
class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;

UENUM()
enum class GameplayAbilityInputs : uint8
{
	UseAbility1,
	UseAbility2
};


UCLASS()
class FOREIGNSEA_API AFS_PlayerPawn : public AFS_GenericPawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFS_PlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	DeclareJcoDebug;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	float TurnSpeed = 10;
	
	UPROPERTY()
	APlayerController* PlayerController;



	/**  */
	UPROPERTY(VisibleDefaultsOnly, Category = "Abilities")
	UAttributeSet* AttributeSet;
	
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void Rotate(float Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//quand on est possessed
	virtual void PossessedBy(AController* NewController) override;

	void Input_AbilityInputTagPressed(FGameplayTag tag);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite, Category = "Abilities")
	UFS_AbilitySystemComponent* FS_AbilitySystemComponent;
	
};




