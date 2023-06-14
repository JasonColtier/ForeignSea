// Fill out your copyright notice in the Description page of Project Settings.


#include "FS_AbilitySystemComponent.h"

#include "ForeignSea/ForeignSeaGameModeBase.h"
#include "ForeignSea/GAS/FS_GameplayAbility.h"


// Sets default values for this component's properties
UFS_AbilitySystemComponent::UFS_AbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFS_AbilitySystemComponent::ProcessInput(const float DeltaTime, const bool bGamePaused)
{
	//if input pressed !
	for (auto Ability : HeldAbilities)
	{
		TryActivateAbility(Ability);
	}
}

void UFS_AbilitySystemComponent::GrantAbility(TSubclassOf<UFS_GameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{
	if(IsValid(AbilityClass))
	{
		//create an object 
		UFS_GameplayAbility* Ability = AbilityClass->GetDefaultObject<UFS_GameplayAbility>();

		if(IsValid(Ability))
		{
			//struct for our ability
			FGameplayAbilitySpec AbilitySpec(
			Ability,
			Level,
			InputCode
			);

			switch (Ability->ActivationPolicy)
			{
			case HeldInput :
				HeldAbilities.AddUnique(AbilitySpec.Handle);
				break;
			case Click :
				default:
				ClickedAbilities.AddUnique(AbilitySpec.Handle);
				break;
			}

			GiveAbility(AbilitySpec);
		}
	}
}

void UFS_AbilitySystemComponent::AbilityInputTagPressed()
{
	//add to pressed array
	// TRACE_SCREEN(0,"tag pressed !! %s",*Tag.GetTagName().ToString());
}

void UFS_AbilitySystemComponent::AbilityInputTagReleased(FGameplayTag Tag)
{
	//remove 
}


// Called when the game starts
void UFS_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFS_AbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

