// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "..\Inputs\FCustomInputBindingToTag.h"
#include "FS_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOREIGNSEA_API UFS_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere)
	TArray<FCustomInputBindingToTag> InputBindings;
	
	// Sets default values for this component's properties
	UFS_AbilitySystemComponent();

	//cycles through the granted abilities and tries to activate the ones for which we press the associated input
	virtual void ProcessInput(const float DeltaTime, const bool bGamePaused);

	UFUNCTION(BlueprintCallable)
	void GrantAbility(TSubclassOf<UFS_GameplayAbility> AbilityClass,int32 Level,int32 InputCode,FGameplayTag tag);

	//binding of input functions. Will be called when the input is pressed, the tag is the identifier of an ability
	void Input_AbilityInputTagPressed(FGameplayTag tag);
	void Input_AbilityInputTagReleased(FGameplayTag tag);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//the tags corresponding to the inputs pressed this frame
	UPROPERTY()
	TArray<FGameplayTag> TagsInputsPressed;

	//an array of abilities that are activated by being held
	UPROPERTY()
	TMap<FGameplayTag,FGameplayAbilitySpecHandle> HeldAbilities;

	//an array of clicked abilities
	UPROPERTY()
	TMap<FGameplayTag,FGameplayAbilitySpecHandle> ClickedAbilities;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
