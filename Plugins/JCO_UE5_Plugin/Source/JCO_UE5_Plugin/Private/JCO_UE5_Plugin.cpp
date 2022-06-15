// Copyright Epic Games, Inc. All Rights Reserved.

#include "JCO_UE5_Plugin.h"

#define LOCTEXT_NAMESPACE "FJCO_UE5_PluginModule"

void FJCO_UE5_PluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FJCO_UE5_PluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FJCO_UE5_PluginModule, JCO_UE5_Plugin)