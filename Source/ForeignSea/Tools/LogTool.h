﻿#ifndef LogTool_H
#define LogTool_H

// Copyright Epic Games, Inc. All Rights Reserved.
#include "CoreMinimal.h"
DECLARE_LOG_CATEGORY_EXTERN(FS_Log, Log, All);

#if _MSC_VER
#define FUNC_NAME    *FString(__func__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT(__func__)
#endif

#define TRACE(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(FS_Log, Log, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
}

#define TRACE_WARNING(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(FS_Log, Warning, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
}

#define TRACE_ERROR(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(FS_Log, Error, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
}

#define TRACE_SCREEN(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
if (Msg == "") \
{ \
TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
FCString::Sprintf(StdMsg, TEXT("%s() : %s"), FUNC_NAME, *GetNameSafe(this)); \
GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, StdMsg); \
UE_LOG(LogTemp, Warning, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
} \
else \
{ \
GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, Msg); \
UE_LOG(FS_Log, Warning, TEXT("%s() : %s"), FUNC_NAME, *Msg);\
} \
}

#endif

