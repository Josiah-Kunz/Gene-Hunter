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
	GENEHUNTER_API UClass* Z_Construct_UClass_UAttackModifier_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UAttackModifier();
	ENGINE_API UClass* Z_Construct_UClass_UUserDefinedStruct();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
// End Cross Module References
	void UAttackModifier::StaticRegisterNativesUAttackModifier()
	{
	}
	UClass* Z_Construct_UClass_UAttackModifier_NoRegister()
	{
		return UAttackModifier::StaticClass();
	}
	struct Z_Construct_UClass_UAttackModifier_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAttackModifier_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserDefinedStruct,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAttackModifier_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "AttackModifier.h" },
		{ "ModuleRelativePath", "AttackModifier.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAttackModifier_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAttackModifier>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAttackModifier_Statics::ClassParams = {
		&UAttackModifier::StaticClass,
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
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAttackModifier_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAttackModifier_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAttackModifier()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAttackModifier_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAttackModifier, 3018319012);
	template<> GENEHUNTER_API UClass* StaticClass<UAttackModifier>()
	{
		return UAttackModifier::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAttackModifier(Z_Construct_UClass_UAttackModifier, &UAttackModifier::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UAttackModifier"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAttackModifier);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
