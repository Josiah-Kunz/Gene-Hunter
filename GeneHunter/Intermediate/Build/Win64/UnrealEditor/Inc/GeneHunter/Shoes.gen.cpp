// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/Shoes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeShoes() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UShoes_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UShoes();
	ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
// End Cross Module References
	void UShoes::StaticRegisterNativesUShoes()
	{
	}
	UClass* Z_Construct_UClass_UShoes_NoRegister()
	{
		return UShoes::StaticClass();
	}
	struct Z_Construct_UClass_UShoes_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ShoeSize_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ShoeSize;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UShoes_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UShoes_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Shoes.h" },
		{ "ModuleRelativePath", "Shoes.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UShoes_Statics::NewProp_ShoeSize_MetaData[] = {
		{ "Category", "Shoes" },
		{ "ModuleRelativePath", "Shoes.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UShoes_Statics::NewProp_ShoeSize = { "ShoeSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UShoes, ShoeSize), METADATA_PARAMS(Z_Construct_UClass_UShoes_Statics::NewProp_ShoeSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UShoes_Statics::NewProp_ShoeSize_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UShoes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UShoes_Statics::NewProp_ShoeSize,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UShoes_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UShoes>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UShoes_Statics::ClassParams = {
		&UShoes::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UShoes_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UShoes_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UShoes_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UShoes_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UShoes()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UShoes_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UShoes, 1985601158);
	template<> GENEHUNTER_API UClass* StaticClass<UShoes>()
	{
		return UShoes::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UShoes(Z_Construct_UClass_UShoes, &UShoes::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UShoes"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UShoes);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
