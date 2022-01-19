// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/SupportingText.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSupportingText() {}
// Cross Module References
	GENEHUNTER_API UScriptStruct* Z_Construct_UScriptStruct_FSupportingText();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
// End Cross Module References
class UScriptStruct* FSupportingText::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern GENEHUNTER_API uint32 Get_Z_Construct_UScriptStruct_FSupportingText_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSupportingText, Z_Construct_UPackage__Script_GeneHunter(), TEXT("SupportingText"), sizeof(FSupportingText), Get_Z_Construct_UScriptStruct_FSupportingText_Hash());
	}
	return Singleton;
}
template<> GENEHUNTER_API UScriptStruct* StaticStruct<FSupportingText>()
{
	return FSupportingText::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSupportingText(FSupportingText::StaticStruct, TEXT("/Script/GeneHunter"), TEXT("SupportingText"), false, nullptr, nullptr);
static struct FScriptStruct_GeneHunter_StaticRegisterNativesFSupportingText
{
	FScriptStruct_GeneHunter_StaticRegisterNativesFSupportingText()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SupportingText")),new UScriptStruct::TCppStructOps<FSupportingText>);
	}
} ScriptStruct_GeneHunter_StaticRegisterNativesFSupportingText;
	struct Z_Construct_UScriptStruct_FSupportingText_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DevNote_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_DevNote;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_Description;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FlavorText_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_FlavorText;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSupportingText_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "SupportingText.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSupportingText_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSupportingText>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_DevNote_MetaData[] = {
		{ "Category", "SupportingText" },
		{ "Comment", "/*\n\x09 * The DevNote is for developers and is in-editor only. It will not be displayed in-game.\n\x09 */" },
		{ "ModuleRelativePath", "SupportingText.h" },
		{ "ToolTip", "* The DevNote is for developers and is in-editor only. It will not be displayed in-game." },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_DevNote = { "DevNote", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSupportingText, DevNote), METADATA_PARAMS(Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_DevNote_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_DevNote_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_Description_MetaData[] = {
		{ "Category", "SupportingText" },
		{ "Comment", "/*\n\x09 * The Description is helpful text that will be displayed in-game.\n\x09 */" },
		{ "ModuleRelativePath", "SupportingText.h" },
		{ "ToolTip", "* The Description is helpful text that will be displayed in-game." },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSupportingText, Description), METADATA_PARAMS(Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_Description_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_Description_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_FlavorText_MetaData[] = {
		{ "Category", "SupportingText" },
		{ "Comment", "/*\n\x09 * The FlavorText is funny or lore-based text. It is pseudo-hidden in-game (e.g., on hover of the description). \n\x09 */" },
		{ "ModuleRelativePath", "SupportingText.h" },
		{ "ToolTip", "* The FlavorText is funny or lore-based text. It is pseudo-hidden in-game (e.g., on hover of the description)." },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_FlavorText = { "FlavorText", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSupportingText, FlavorText), METADATA_PARAMS(Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_FlavorText_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_FlavorText_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSupportingText_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_DevNote,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_Description,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSupportingText_Statics::NewProp_FlavorText,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSupportingText_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
		nullptr,
		&NewStructOps,
		"SupportingText",
		sizeof(FSupportingText),
		alignof(FSupportingText),
		Z_Construct_UScriptStruct_FSupportingText_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSupportingText_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSupportingText_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSupportingText_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSupportingText()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSupportingText_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_GeneHunter();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SupportingText"), sizeof(FSupportingText), Get_Z_Construct_UScriptStruct_FSupportingText_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UECodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSupportingText_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSupportingText_Hash() { return 3214487478U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
