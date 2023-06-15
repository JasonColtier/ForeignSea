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

	virtual void ProcessInput(const float DeltaTime, const bool bGamePaused);

	UFUNCTION(BlueprintCallable)
	void GrantAbility(TSubclassOf<UFS_GameplayAbility> AbilityClass,int32 Level,int32 InputCode,FGameplayTag tag);
	
	void Input_AbilityInputTagPressed(FGameplayTag tag);
	void Input_AbilityInputTagReleased(FGameplayTag tag);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	UPROPERTY()
	TArray<FGameplayTag> TagsInputsPressed;

	UPROPERTY()
	TMap<FGameplayTag,FGameplayAbilitySpecHandle> HeldAbilities;

	UPROPERTY()
	TMap<FGameplayTag,FGameplayAbilitySpecHandle> ClickedAbilities;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
