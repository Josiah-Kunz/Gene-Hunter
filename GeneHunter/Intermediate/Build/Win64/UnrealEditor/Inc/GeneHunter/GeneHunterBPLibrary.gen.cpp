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
// End Cross Module References
	DEFINE_FUNCTION(UGeneHunterBPLibrary::execEnsureValidAssetName)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Filename);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UGeneHunterBPLibrary::EnsureValidAssetName(Z_Param_Filename);
		P_NATIVE_END;
	}
	void UGeneHunterBPLibrary::StaticRegisterNativesUGeneHunterBPLibrary()
	{
		UClass* Class = UGeneHunterBPLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EnsureValidAssetName", &UGeneHunterBPLibrary::execEnsureValidAssetName },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics
	{
		struct GeneHunterBPLibrary_eventEnsureValidAssetName_Parms
		{
			FString Filename;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Filename_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Filename;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_Filename,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GeneHunterBPLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneHunterBPLibrary, nullptr, "EnsureValidAssetName", nullptr, nullptr, sizeof(GeneHunterBPLibrary_eventEnsureValidAssetName_Parms), Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName_Statics::FuncParams);
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
		{ &Z_Construct_UFunction_UGeneHunterBPLibrary_EnsureValidAssetName, "EnsureValidAssetName" }, // 3145599045
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
	IMPLEMENT_CLASS(UGeneHunterBPLibrary, 2456486520);
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
