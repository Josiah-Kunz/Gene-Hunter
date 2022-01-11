// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/PlantRowAssetTwo.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlantRowAssetTwo() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UPlantRowAssetTwo_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UPlantRowAssetTwo();
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
// End Cross Module References
	void UPlantRowAssetTwo::StaticRegisterNativesUPlantRowAssetTwo()
	{
	}
	UClass* Z_Construct_UClass_UPlantRowAssetTwo_NoRegister()
	{
		return UPlantRowAssetTwo::StaticClass();
	}
	struct Z_Construct_UClass_UPlantRowAssetTwo_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FlowerRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FlowerRadius;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UPlantRowAssetTwo_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPlantRowAssetTwo_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "PlantRowAssetTwo.h" },
		{ "ModuleRelativePath", "PlantRowAssetTwo.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_DisplayName_MetaData[] = {
		{ "Category", "PlantRowAssetTwo" },
		{ "ModuleRelativePath", "PlantRowAssetTwo.h" },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPlantRowAssetTwo, DisplayName), METADATA_PARAMS(Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_DisplayName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_DisplayName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_FlowerRadius_MetaData[] = {
		{ "Category", "PlantRowAssetTwo" },
		{ "ModuleRelativePath", "PlantRowAssetTwo.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_FlowerRadius = { "FlowerRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UPlantRowAssetTwo, FlowerRadius), METADATA_PARAMS(Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_FlowerRadius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_FlowerRadius_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPlantRowAssetTwo_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_DisplayName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPlantRowAssetTwo_Statics::NewProp_FlowerRadius,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UPlantRowAssetTwo_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPlantRowAssetTwo>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UPlantRowAssetTwo_Statics::ClassParams = {
		&UPlantRowAssetTwo::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UPlantRowAssetTwo_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UPlantRowAssetTwo_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UPlantRowAssetTwo_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UPlantRowAssetTwo_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UPlantRowAssetTwo()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UPlantRowAssetTwo_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UPlantRowAssetTwo, 1908034636);
	template<> GENEHUNTER_API UClass* StaticClass<UPlantRowAssetTwo>()
	{
		return UPlantRowAssetTwo::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UPlantRowAssetTwo(Z_Construct_UClass_UPlantRowAssetTwo, &UPlantRowAssetTwo::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UPlantRowAssetTwo"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UPlantRowAssetTwo);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
