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

	/*
	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
	*/
	
	//i'm looking for all the abilities that should activate when held
	for (auto Ability : HeldAbilities)
	{
		//if it matches the specific ability tag that is pressed this frame
		if(TagsInputsPressed.Contains(Ability.Key))
		{
			//we try to activate it. 
			TryActivateAbility(Ability.Value);
			TRACE("active input %s : activating ability ! ",*Ability.Key.GetTagName().ToString());
		}
	}
}

void UFS_AbilitySystemComponent::GrantAbility(TSubclassOf<UFS_GameplayAbility> AbilityClass, int32 Level, int32 InputCode,FGameplayTag tag)
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
				HeldAbilities.Add(tag,AbilitySpec.Handle);
				break;
			case Click :
				default:
				ClickedAbilities.Add(tag,AbilitySpec.Handle);
				break;
			}

			GiveAbility(AbilitySpec);
		}
	}
}


void UFS_AbilitySystemComponent::Input_AbilityInputTagPressed(FGameplayTag tag)
{
	TagsInputsPressed.AddUnique(tag);
}

void UFS_AbilitySystemComponent::Input_AbilityInputTagReleased(FGameplayTag tag)
{
	TagsInputsPressed.Remove(tag);
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

