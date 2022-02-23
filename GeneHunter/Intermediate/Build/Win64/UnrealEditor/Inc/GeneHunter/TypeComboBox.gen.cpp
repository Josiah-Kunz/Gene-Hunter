// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/TypeComboBox.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTypeComboBox() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UTypeComboBox_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UTypeComboBox();
	UMG_API UClass* Z_Construct_UClass_UComboBoxString();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
// End Cross Module References
	void UTypeComboBox::StaticRegisterNativesUTypeComboBox()
	{
	}
	UClass* Z_Construct_UClass_UTypeComboBox_NoRegister()
	{
		return UTypeComboBox::StaticClass();
	}
	struct Z_Construct_UClass_UTypeComboBox_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTypeComboBox_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UComboBoxString,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTypeComboBox_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "TypeComboBox.h" },
		{ "ModuleRelativePath", "TypeComboBox.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTypeComboBox_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTypeComboBox>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UTypeComboBox_Statics::ClassParams = {
		&UTypeComboBox::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UTypeComboBox_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UTypeComboBox_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UTypeComboBox()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UTypeComboBox_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UTypeComboBox, 145508725);
	template<> GENEHUNTER_API UClass* StaticClass<UTypeComboBox>()
	{
		return UTypeComboBox::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UTypeComboBox(Z_Construct_UClass_UTypeComboBox, &UTypeComboBox::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UTypeComboBox"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTypeComboBox);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
