// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_BTTask_SetRotationToPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ForeignSea/Characters/FS_EnemyPawn.h"
#include "ForeignSea/Characters/SF_AIController.h"

EBTNodeResult::Type USF_BTTask_SetRotationToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	MyBlackboard = OwnerComp.GetBlackboardComponent();

	if(!OwnerPawn)
	OwnerPawn = Cast<AFS_EnemyPawn>(Cast<ASF_AIController>(OwnerComp.GetOwner())->GetPawn());

	if(!PlayerPawn)
	PlayerPawn = Cast<AFS_GenericPawn>(MyBlackboard->GetValueAsObject("PlayerPawn"));
		
	OwnerPawn->LocationToRotateToward = PlayerPawn->GetActorLocation();
	
	return EBTNodeResult::Succeeded;
}
