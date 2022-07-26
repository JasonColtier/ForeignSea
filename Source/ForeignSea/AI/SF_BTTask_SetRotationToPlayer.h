// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SF_BTTask_SetRotationToPlayer.generated.h"

class AFS_GenericPawn;
class AFS_EnemyPawn;
/**
 * 
 */
UCLASS()
class FOREIGNSEA_API USF_BTTask_SetRotationToPlayer : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY()
	UBlackboardComponent* MyBlackboard;

	UPROPERTY()
	AFS_EnemyPawn* OwnerPawn;

	UPROPERTY()
	AFS_GenericPawn* PlayerPawn;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
