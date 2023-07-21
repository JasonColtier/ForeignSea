// Fill out your copyright notice in the Description page of Project Settings.


#include "VUEditorSubsystem.h"
#include "GeneralProjectSettings.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"
#include "LogTool.h"
#include "SourceControlOperations.h"
#include "Misc/DefaultValueHelper.h"

void UVUEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TRACE_WARNING("Updating version");
	UGeneralProjectSettings* projectSettings = GetMutableDefault<UGeneralProjectSettings>();

	FString version = projectSettings->ProjectVersion;
	TRACE_WARNING("Current version %s", *version);

	FString base = "";
	FString end = "";
	version.Split(".", &base, &end, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	TRACE_WARNING("base is %s", *base);
	TRACE_WARNING("end is %s", *end);

	int64 buildNumber;
	if (FDefaultValueHelper::ParseInt64(end, buildNumber))
	{
		buildNumber++;
		FString newVersion = base + "." + FString::FromInt(buildNumber);
		TRACE_WARNING("new version is %s", *newVersion);
		projectSettings->ProjectVersion = newVersion;
		projectSettings->UpdateSinglePropertyInConfigFile(
			projectSettings->GetClass()->FindPropertyByName(
				GET_MEMBER_NAME_CHECKED(UGeneralProjectSettings, ProjectVersion)),
			projectSettings->GetDefaultConfigFilename());

		ISourceControlProvider* SourceControlProvider = &ISourceControlModule::Get().GetProvider();

		if (SourceControlProvider && SourceControlProvider->IsEnabled())
		{
			FString fileVersion = "Game/Config/DefaultGame.ini";
			auto file = SourceControlProvider->GetState(fileVersion, EStateCacheUsage::ForceUpdate);
			check(file && "file not found");

			if (file && file->CanCheckout() && SourceControlProvider->UsesCheckout())
			{
				TArray<FString> filesToCheckout;
				filesToCheckout.Add(fileVersion);
				SourceControlProvider->Execute(ISourceControlOperation::Create<FCheckOut>(), filesToCheckout);
			}
			else
			{
				TRACE_ERROR("file could not be checked out !")
			}
			if (file && file->IsCheckedOut())
			{
				TArray<FString> FilesToBeCheckeIn;
				FilesToBeCheckeIn.Add(fileVersion);

				TSharedRef<FCheckIn> CheckinOperation = ISourceControlOperation::Create<FCheckIn>();
				CheckinOperation->SetDescription(NSLOCTEXT("AutoVersionCommandlet", "UpdateVersion",
				                                           "AUTOMATION: Update Project Version to %s"));

				SourceControlProvider->Execute(CheckinOperation, FilesToBeCheckeIn);
			}else
			{
				TRACE_ERROR("file could not be checked in !")
			}
		}
	}
}
