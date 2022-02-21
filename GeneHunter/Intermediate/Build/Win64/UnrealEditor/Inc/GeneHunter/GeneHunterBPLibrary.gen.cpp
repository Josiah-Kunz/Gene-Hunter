// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/GeneHunterBPLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGeneHunterBPLibrary() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UGeneHunterBPLibrary_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UGeneHunterBPLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FAssetData();
	GENEHUNTER_API UClass* Z_Construct_UClass_UType_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UGeneHunterBPLibrary::execGetAllTypes)
	{
		P_GET_TARRAY_REF(UType*,Z_Param_Out_Types);
		P_GET_TARRAY(UType*,Z_Param_Exclude);
		P_GET_UBOOL(Z_Param_SortABC);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGeneHunterBPLibrary::GetAllTypes(Z_Param_Out_Types,Z_Param_Exclude,Z_Param_SortABC);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGeneHunterBPLibrary::execGetAllTypeAssets)
	{
		P_GET_TARRAY_REF(FAssetData,Z_Param_Out_TypeAssets);
		P_GET_UBOOL(Z_Param_SortABC);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGeneHunterBPLibrary::GetAllTypeAssets(Z_Param_Out_TypeAssets,Z_Param_SortABC);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGeneHunterBPLibrary::execPruneTypeAttackMods)
	{
		P_GET_OBJECT(UType,Z_Param_Type);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGeneHunterBPLibrary::PruneTypeAttackMods(Z_Param_Type);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGeneHunterBPLibrary::execSaveLoadedAssetFromAnywhere)
	{
		P_GET_OBJECT(UObject,Z_Param_Asset);
		P_GET_UBOOL(Z_Param_bOnlyIfDirty);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=UGeneHunterBPLibrary::SaveLoadedAssetFromAnywhere(Z_Param_Asset,Z_Param_bOnlyIfDirty);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGeneHunterBPLibrary::execSortAssetsAlphabetically)
	{
		P_GET_TARRAY(FAssetData,Z_Param_Assets);
		P_GET_TARRAY_REF(FAssetData,Z_Param_Out_Sorted);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGeneHunterBPLibrary::SortAssetsAlphabetically(Z_Param_Assets,Z_Param_Out_Sorted);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGeneHunterBPLibrary::execEnsureValidAssetName)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Filename);
		P_GET_PROPERTY(FStrProperty,Z_Param_Path);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_SafeFilename);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_AbsolutePath);
		P_GET_PROPERTY(FStrProperty,Z_Param_Ext);
		P_GET_PROPERTY(FStrProperty,Z_Param_OldFilename);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGeneHunterBPLibrary::EnsureValidAssetName(Z_Param_Filename,Z_Param_Path,Z_Param_Out_SafeFilename,Z_Param_Out_AbsolutePath,Z_Param_Ext,Z_Param_OldFilename);
		P_NATIVE_END;
	}
	void UGeneHunterBPLibrary::StaticRegisterNativesUGeneHunterBPLibrary()
	{
		UClass* Class = UGeneHunterBPLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EnsureValidAssetName", &UGeneHunterBPLibrary::execEnsureValidAssetName },
			{ "GetAllTypeAssets", &UGeneHunterBPLibrary::execGetAllTypeAssets },
			{ "GetAllTypes", &UGeneHunterBPLibrary::execGetAllTypes },
			{ "PruneTypeAttackMods", &UGeneHunterBPLibrary::execPruneTypeAttackMods },
			{ "SaveLoadedAssetFromAnywhere", &UGeneHunterBPLibrary::execSaveLoadedAssetFromAnywhere },
			{ "SortAssetsAlphabetically", &UGeneHunterBPLibrary::execSortAssetsAlphabetically },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics
	{
		struct GeneHunterBPLibrary_eventEnsureValidAssetName_Parms
		{
			FString Filename;
			FString Path;
			FString SafeFilename;
			FString AbsolutePath;
			FString Ext;
			FString OldFilename;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Filename_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Filename;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Path;
		static const UECodeGen_Private::FStrPropertyParams NewProp_SafeFilename;
		static const UECodeGen_Private::FStrPropertyParams NewProp_AbsolutePath;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Ext_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Ext;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OldFilename_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_OldFilename;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Filename_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Filename = { "Filename", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms, Filename), METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Filename_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Filename_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Path_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms, Path), METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Path_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Path_MetaData)) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_SafeFilename = { "SafeFilename", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms, SafeFilename), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_AbsolutePath = { "AbsolutePath", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms, AbsolutePath), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Ext_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Ext = { "Ext", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms, Ext), METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Ext_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Ext_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_OldFilename_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_OldFilename = { "OldFilename", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms, OldFilename), METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_OldFilename_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_OldFilename_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Filename,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Path,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_SafeFilename,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_AbsolutePath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Ext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_OldFilename,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_Ext", "uasset" },
		{ "CPP_Default_OldFilename", "" },
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneHunterBPLibrary, nullptr, "EnsureValidAssetName", nullptr, nullptr, sizeof(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms), Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics
	{
		struct GeneHunterBPLibrary_eventGetAllTypeAssets_Parms
		{
			TArray<FAssetData> TypeAssets;
			bool SortABC;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_TypeAssets_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_TypeAssets;
		static void NewProp_SortABC_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_SortABC;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_TypeAssets_Inner = { "TypeAssets", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FAssetData, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_TypeAssets = { "TypeAssets", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventGetAllTypeAssets_Parms, TypeAssets), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_SortABC_SetBit(void* Obj)
	{
		((GeneHunterBPLibrary_eventGetAllTypeAssets_Parms*)Obj)->SortABC = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_SortABC = { "SortABC", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(GeneHunterBPLibrary_eventGetAllTypeAssets_Parms), &Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_SortABC_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_TypeAssets_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_TypeAssets,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::NewProp_SortABC,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_SortABC", "false" },
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneHunterBPLibrary, nullptr, "GetAllTypeAssets", nullptr, nullptr, sizeof(GeneHunterBPLibrary_eventGetAllTypeAssets_Parms), Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics
	{
		struct GeneHunterBPLibrary_eventGetAllTypes_Parms
		{
			TArray<UType*> Types;
			TArray<UType*> Exclude;
			bool SortABC;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Types_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Types;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Exclude_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Exclude;
		static void NewProp_SortABC_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_SortABC;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Types_Inner = { "Types", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Types = { "Types", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventGetAllTypes_Parms, Types), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Exclude_Inner = { "Exclude", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Exclude = { "Exclude", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventGetAllTypes_Parms, Exclude), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_SortABC_SetBit(void* Obj)
	{
		((GeneHunterBPLibrary_eventGetAllTypes_Parms*)Obj)->SortABC = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_SortABC = { "SortABC", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(GeneHunterBPLibrary_eventGetAllTypes_Parms), &Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_SortABC_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Types_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Types,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Exclude_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_Exclude,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::NewProp_SortABC,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "Exclude" },
		{ "CPP_Default_SortABC", "true" },
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneHunterBPLibrary, nullptr, "GetAllTypes", nullptr, nullptr, sizeof(GeneHunterBPLibrary_eventGetAllTypes_Parms), Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics
	{
		struct GeneHunterBPLibrary_eventPruneTypeAttackMods_Parms
		{
			UType* Type;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Type;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventPruneTypeAttackMods_Parms, Type), Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::NewProp_Type,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneHunterBPLibrary, nullptr, "PruneTypeAttackMods", nullptr, nullptr, sizeof(GeneHunterBPLibrary_eventPruneTypeAttackMods_Parms), Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics
	{
		struct GeneHunterBPLibrary_eventSaveLoadedAssetFromAnywhere_Parms
		{
			UObject* Asset;
			bool bOnlyIfDirty;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Asset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bOnlyIfDirty_MetaData[];
#endif
		static void NewProp_bOnlyIfDirty_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bOnlyIfDirty;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_Asset = { "Asset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventSaveLoadedAssetFromAnywhere_Parms, Asset), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_bOnlyIfDirty_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_bOnlyIfDirty_SetBit(void* Obj)
	{
		((GeneHunterBPLibrary_eventSaveLoadedAssetFromAnywhere_Parms*)Obj)->bOnlyIfDirty = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_bOnlyIfDirty = { "bOnlyIfDirty", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(GeneHunterBPLibrary_eventSaveLoadedAssetFromAnywhere_Parms), &Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_bOnlyIfDirty_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_bOnlyIfDirty_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_bOnlyIfDirty_MetaData)) };
	void Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GeneHunterBPLibrary_eventSaveLoadedAssetFromAnywhere_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(GeneHunterBPLibrary_eventSaveLoadedAssetFromAnywhere_Parms), &Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_Asset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_bOnlyIfDirty,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::Function_MetaDataParams[] = {
		{ "CPP_Default_bOnlyIfDirty", "true" },
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneHunterBPLibrary, nullptr, "SaveLoadedAssetFromAnywhere", nullptr, nullptr, sizeof(GeneHunterBPLibrary_eventSaveLoadedAssetFromAnywhere_Parms), Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics
	{
		struct GeneHunterBPLibrary_eventSortAssetsAlphabetically_Parms
		{
			TArray<FAssetData> Assets;
			TArray<FAssetData> Sorted;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_Assets_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Assets_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Assets;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Sorted_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Sorted;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Assets_Inner = { "Assets", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FAssetData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Assets_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Assets = { "Assets", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventSortAssetsAlphabetically_Parms, Assets), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Assets_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Assets_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Sorted_Inner = { "Sorted", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FAssetData, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Sorted = { "Sorted", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventSortAssetsAlphabetically_Parms, Sorted), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Assets_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Assets,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Sorted_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::NewProp_Sorted,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneHunterBPLibrary, nullptr, "SortAssetsAlphabetically", nullptr, nullptr, sizeof(GeneHunterBPLibrary_eventSortAssetsAlphabetically_Parms), Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGeneHunterBPLibrary_NoRegister()
	{
		return UGeneHunterBPLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UGeneHunterBPLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGeneHunterBPLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGeneHunterBPLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName, "EnsureValidAssetName" }, // 1396083631
		{ &Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypeAssets, "GetAllTypeAssets" }, // 3696337972
		{ &Z_Construct_UFunction_UGeneHunterBPLibrary_GetAllTypes, "GetAllTypes" }, // 760130562
		{ &Z_Construct_UFunction_UGeneHunterBPLibrary_PruneTypeAttackMods, "PruneTypeAttackMods" }, // 2433913900
		{ &Z_Construct_UFunction_UGeneHunterBPLibrary_SaveLoadedAssetFromAnywhere, "SaveLoadedAssetFromAnywhere" }, // 2606620303
		{ &Z_Construct_UFunction_UGeneHunterBPLibrary_SortAssetsAlphabetically, "SortAssetsAlphabetically" }, // 3125384306
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGeneHunterBPLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "GeneHunterBPLibrary.h" },
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGeneHunterBPLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGeneHunterBPLibrary>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGeneHunterBPLibrary_Statics::ClassParams = {
		&UGeneHunterBPLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGeneHunterBPLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGeneHunterBPLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGeneHunterBPLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGeneHunterBPLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGeneHunterBPLibrary, 406139645);
	template<> GENEHUNTER_API UClass* StaticClass<UGeneHunterBPLibrary>()
	{
		return UGeneHunterBPLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGeneHunterBPLibrary(Z_Construct_UClass_UGeneHunterBPLibrary, &UGeneHunterBPLibrary::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UGeneHunterBPLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGeneHunterBPLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
