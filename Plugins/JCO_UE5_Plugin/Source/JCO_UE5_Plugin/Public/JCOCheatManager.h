// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "JCOCheatManager.generated.h"

/**
 * Cette classe permet de faire des check pour les débugs
 */
UCLASS()
class JCO_UE5_PLUGIN_API UJCOCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	/**
	 * @brief Active ou pas le débug, accessible depuis la console commande
	 */
	UFUNCTION(Exec, CallInEditor,Category = "JCO Debug")
	void ToggleDebug();
	
	/**
	 * @brief Est ce que le debug est activé?
	 */
	UPROPERTY(EditAnywhere,Category = "JCO Debug")
	bool DebugActivated;

	/**
 * @brief Declare la propriété UJcoGameInstanceSubsystem;
 */
#define DeclareJcoDebug \
	UPROPERTY()\
	UJcoGameInstanceSubsystem* JcoGameInstanceSubsystem;

	/**
 * @brief Sets the JcoGameInstanceSubsystem from the gameInstance
 */
#define SetJcoGameInstance\
	JcoGameInstanceSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UJcoGameInstanceSubsystem>();

	/**
 * @brief To use the debug, we first need to use SetJcoGameInstance in begin play and DeclareJcoDebug in header
 * used like that :
	* Debug \n
	{\n
		TRACE_ERROR("Ticking log : debug ");\n
	}
 */
#define Debug \
	check(JcoGameInstanceSubsystem != nullptr)\
	if(JcoGameInstanceSubsystem->CheatManager != nullptr && JcoGameInstanceSubsystem->CheatManager->DebugActivated)

private:
	/**
 * @brief Initialisation de la classe, se renseigne au près du JcoGameInstanceSubsystem
 */
	virtual void InitCheatManager() override;
};
