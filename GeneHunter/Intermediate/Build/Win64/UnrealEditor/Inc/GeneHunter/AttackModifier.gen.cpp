// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/AttackModifier.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAttackModifier() {}
// Cross Module References
	GENEHUNTER_API UScriptStruct* Z_Construct_UScriptStruct_FAttackModifier();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
	GENEHUNTER_API UScriptStruct* Z_Construct_UScriptStruct_FSupportingText();
// End Cross Module References
class UScriptStruct* FAttackModifier::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern GENEHUNTER_API uint32 Get_Z_Construct_UScriptStruct_FAttackModifier_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAttackModifier, Z_Construct_UPackage__Script_GeneHunter(), TEXT("AttackModifier"), sizeof(FAttackModifier), Get_Z_Construct_UScriptStruct_FAttackModifier_Hash());
	}
	return Singleton;
}
template<> GENEHUNTER_API UScriptStruct* StaticStruct<FAttackModifier>()
{
	return FAttackModifier::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAttackModifier(FAttackModifier::StaticStruct, TEXT("/Script/GeneHunter"), TEXT("AttackModifier"), false, nullptr, nullptr);
static struct FScriptStruct_GeneHunter_StaticRegisterNativesFAttackModifier
{
	FScriptStruct_GeneHunter_StaticRegisterNativesFAttackModifier()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AttackModifier")),new UScriptStruct::TCppStructOps<FAttackModifier>);
	}
} ScriptStruct_GeneHunter_StaticRegisterNativesFAttackModifier;
	struct Z_Construct_UScriptStruct_FAttackModifier_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Modifier_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Modifier;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SupportingText_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_SupportingText;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAttackModifier_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "AttackModifier.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAttackModifier_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAttackModifier>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_Modifier_MetaData[] = {
		{ "Category", "AttackModifier" },
		{ "ModuleRelativePath", "AttackModifier.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_Modifier = { "Modifier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAttackModifier, Modifier), METADATA_PARAMS(Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_Modifier_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_Modifier_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_SupportingText_MetaData[] = {
		{ "Category", "AttackModifier" },
		{ "ModuleRelativePath", "AttackModifier.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_SupportingText = { "SupportingText", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAttackModifier, SupportingText), Z_Construct_UScriptStruct_FSupportingText, METADATA_PARAMS(Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_SupportingText_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_SupportingText_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAttackModifier_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_Modifier,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAttackModifier_Statics::NewProp_SupportingText,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAttackModifier_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
		nullptr,
		&NewStructOps,
		"AttackModifier",
		sizeof(FAttackModifier),
		alignof(FAttackModifier),
		Z_Construct_UScriptStruct_FAttackModifier_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAttackModifier_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAttackModifier_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAttackModifier_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAttackModifier()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAttackModifier_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_GeneHunter();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AttackModifier"), sizeof(FAttackModifier), Get_Z_Construct_UScriptStruct_FAttackModifier_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UECodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAttackModifier_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAttackModifier_Hash() { return 3633297239U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
