// Fill out your copyright notice in the Description page of Project Settings.


#include "JCOCheatManager.h"

#include "JcoGameInstanceSubsystem.h"

void UJCOCheatManager::ToggleDebug()
{
	DebugActivated = !DebugActivated;

	UE_LOG(LogBlueprint, Warning, TEXT("CheatManager : toggle debug : %hdd"),UJCOCheatManager::DebugActivated );
}

void UJCOCheatManager::InitCheatManager()
{
	Super::InitCheatManager();

	GetWorld()->GetGameInstance()->GetSubsystem<UJcoGameInstanceSubsystem>()->CheatManager = this;
}
