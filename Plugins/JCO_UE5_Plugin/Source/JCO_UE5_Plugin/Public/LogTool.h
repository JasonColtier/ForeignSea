#ifndef LogTool_H
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
UE_LOG(FS_Log, Log, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
}

#define TRACE_WARNING(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(FS_Log, Warning, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
}

#define TRACE_ERROR(Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
UE_LOG(FS_Log, Error, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
}

#define TRACE_SCREEN(time,Format, ...) \
{ \
const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
if (Msg == "") \
{ \
TCHAR StdMsg[MAX_SPRINTF] = TEXT(""); \
FCString::Sprintf(StdMsg, TEXT("%s() : %s"), FUNC_NAME, *GetNameSafe(this)); \
GEngine->AddOnScreenDebugMessage(-1, time, FColor::White, StdMsg); \
UE_LOG(FS_Log, Log, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
} \
else \
{ \
GEngine->AddOnScreenDebugMessage(-1, time, FColor::White, Msg); \
UE_LOG(FS_Log, Log, TEXT("%s | %s() [%d] : %s"),*GetNameSafe(this),FUNC_NAME,__LINE__, *Msg);\
} \
}

#endif

