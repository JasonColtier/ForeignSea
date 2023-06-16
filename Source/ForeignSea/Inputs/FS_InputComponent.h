// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "FCustomInputBindingToTag.h"
#include "LogTool.h"
#include "FS_InputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOREIGNSEA_API UFS_InputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFS_InputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//nice templated function allowing to bind InputAction to a function
	template<class UserClass,typename PressedFuncType,typename ReleasedFuncType>
	void BindAbility(UserClass* ObjectClass,PressedFuncType PressedFunc,ReleasedFuncType ReleasedFunc,const TArray<FCustomInputBindingToTag>& CustomInputBindingToTags)
	{
		for (auto Action : CustomInputBindingToTags)
		{
			if(PressedFunc)
				BindAction(Action.Input,ETriggerEvent::Triggered,ObjectClass,PressedFunc,Action.Tag);

			if(ReleasedFunc)
				BindAction(Action.Input,ETriggerEvent::Completed,ObjectClass,ReleasedFunc,Action.Tag);

			UE_LOG(LogBlueprint,Warning,TEXT("binded input %s"),*Action.Tag.GetTagName().ToString());
		}
	}
};
