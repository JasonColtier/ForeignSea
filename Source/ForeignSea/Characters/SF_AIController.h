// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SF_AIController.generated.h"

/**
 * 
 */
UCLASS()
class FOREIGNSEA_API ASF_AIController : public AAIController
{
	GENERATED_BODY()

	ASF_AIController();


private:
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

protected:
	
	virtual void OnPossess(APawn* InPawn) override;
	
};
