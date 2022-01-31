// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/MyEditableTextInCPP.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyEditableTextInCPP() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UMyEditableTextInCPP_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UMyEditableTextInCPP();
	UMG_API UClass* Z_Construct_UClass_UEditableText();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
// End Cross Module References
	void UMyEditableTextInCPP::StaticRegisterNativesUMyEditableTextInCPP()
	{
	}
	UClass* Z_Construct_UClass_UMyEditableTextInCPP_NoRegister()
	{
		return UMyEditableTextInCPP::StaticClass();
	}
	struct Z_Construct_UClass_UMyEditableTextInCPP_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMyEditableTextInCPP_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEditableText,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMyEditableTextInCPP_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "MyEditableTextInCPP.h" },
		{ "ModuleRelativePath", "MyEditableTextInCPP.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMyEditableTextInCPP_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMyEditableTextInCPP>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMyEditableTextInCPP_Statics::ClassParams = {
		&UMyEditableTextInCPP::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UMyEditableTextInCPP_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMyEditableTextInCPP_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMyEditableTextInCPP()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMyEditableTextInCPP_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMyEditableTextInCPP, 1700451257);
	template<> GENEHUNTER_API UClass* StaticClass<UMyEditableTextInCPP>()
	{
		return UMyEditableTextInCPP::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMyEditableTextInCPP(Z_Construct_UClass_UMyEditableTextInCPP, &UMyEditableTextInCPP::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UMyEditableTextInCPP"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMyEditableTextInCPP);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
