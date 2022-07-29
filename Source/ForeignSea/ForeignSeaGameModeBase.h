// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Plugins/JCO_UE5_Plugin/Source/JCO_UE5_Plugin/Public/LogTool.h"
#include "ForeignSeaGameModeBase.generated.h"

class AFS_PlayerPawn;
/**
 * 
 */
UCLASS()
class FOREIGNSEA_API AForeignSeaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	

	virtual void BeginPlay() override;
};
