// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_AIController.h"

#include "FS_PlayerPawn.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ForeignSea/ForeignSeaGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASF_AIController::ASF_AIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void ASF_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	check(BehaviorTree);
	
	RunBehaviorTree(BehaviorTree);

	BlackboardComponent->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));

	AFS_PlayerPawn* PlayerPawn = Cast<AFS_PlayerPawn>(UGameplayStatics::GetPlayerPawn(InPawn,0));
	
	BlackboardComponent->SetValueAsObject("PlayerPawn",PlayerPawn);
}
