// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/Type.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeType() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UType_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UType();
	ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
	GENEHUNTER_API UScriptStruct* Z_Construct_UScriptStruct_FAttackModifier();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
	GENEHUNTER_API UScriptStruct* Z_Construct_UScriptStruct_FSupportingText();
// End Cross Module References
	void UType::StaticRegisterNativesUType()
	{
	}
	UClass* Z_Construct_UClass_UType_NoRegister()
	{
		return UType::StaticClass();
	}
	struct Z_Construct_UClass_UType_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_AttackModifiers_ValueProp;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_AttackModifiers_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackModifiers_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_AttackModifiers;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Colors_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Colors_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Colors;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SupportingText_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_SupportingText;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UType_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UPrimaryDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UType_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Type.h" },
		{ "ModuleRelativePath", "Type.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers_ValueProp = { "AttackModifiers", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UScriptStruct_FAttackModifier, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers_Key_KeyProp = { "AttackModifiers_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers_MetaData[] = {
		{ "Category", "Type" },
		{ "Comment", "/**\n\x09 * A map of modifiers that this Type gets when attacking other Types.\n\x09 **/" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "A map of modifiers that this Type gets when attacking other Types." },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers = { "AttackModifiers", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UType, AttackModifiers), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UType_Statics::NewProp_Colors_Inner = { "Colors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UType_Statics::NewProp_Colors_MetaData[] = {
		{ "Category", "Type" },
		{ "ModuleRelativePath", "Type.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UType_Statics::NewProp_Colors = { "Colors", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UType, Colors), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UType_Statics::NewProp_Colors_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UType_Statics::NewProp_Colors_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UType_Statics::NewProp_SupportingText_MetaData[] = {
		{ "Category", "Type" },
		{ "ModuleRelativePath", "Type.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UType_Statics::NewProp_SupportingText = { "SupportingText", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UType, SupportingText), Z_Construct_UScriptStruct_FSupportingText, METADATA_PARAMS(Z_Construct_UClass_UType_Statics::NewProp_SupportingText_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UType_Statics::NewProp_SupportingText_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UType_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UType_Statics::NewProp_AttackModifiers,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UType_Statics::NewProp_Colors_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UType_Statics::NewProp_Colors,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UType_Statics::NewProp_SupportingText,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UType_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UType>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UType_Statics::ClassParams = {
		&UType::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UType_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UType_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UType_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UType_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UType()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UType_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UType, 4111829168);
	template<> GENEHUNTER_API UClass* StaticClass<UType>()
	{
		return UType::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UType(Z_Construct_UClass_UType, &UType::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UType"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UType);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
