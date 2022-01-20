// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GENEHUNTER_TypeAdvantageEditorEnums_generated_h
#error "TypeAdvantageEditorEnums.generated.h already included, missing '#pragma once' in TypeAdvantageEditorEnums.h"
#endif
#define GENEHUNTER_TypeAdvantageEditorEnums_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GeneHunter_Source_GeneHunter_TypeAdvantageEditorEnums_h


#define FOREACH_ENUM_TATEXT(op) \
	op(TAText::DevNote) \
	op(TAText::Description) \
	op(TAText::FlavorText) 

enum class TAText : uint8;
template<> GENEHUNTER_API UEnum* StaticEnum<TAText>();

#define FOREACH_ENUM_TAQUEUESTATUS(op) \
	op(TAQueueStatus::Idle) \
	op(TAQueueStatus::Rename) 

enum class TAQueueStatus : uint8;
template<> GENEHUNTER_API UEnum* StaticEnum<TAQueueStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
