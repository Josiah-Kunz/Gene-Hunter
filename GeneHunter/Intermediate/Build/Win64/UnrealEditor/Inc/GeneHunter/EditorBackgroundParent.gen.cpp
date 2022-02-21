// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/EditorBackgroundParent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditorBackgroundParent() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UEditorBackgroundParent_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UEditorBackgroundParent();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
// End Cross Module References
	void UEditorBackgroundParent::StaticRegisterNativesUEditorBackgroundParent()
	{
	}
	UClass* Z_Construct_UClass_UEditorBackgroundParent_NoRegister()
	{
		return UEditorBackgroundParent::StaticClass();
	}
	struct Z_Construct_UClass_UEditorBackgroundParent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ClickOffButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ClickOffButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Width;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEditorBackgroundParent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEditorBackgroundParent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * A class to augment the EditorBackground class. Mostly used to give the dev access to the width of the \"right menu\".\n */" },
		{ "IncludePath", "EditorBackgroundParent.h" },
		{ "ModuleRelativePath", "EditorBackgroundParent.h" },
		{ "ToolTip", "A class to augment the EditorBackground class. Mostly used to give the dev access to the width of the \"right menu\"." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_ClickOffButton_MetaData[] = {
		{ "Category", "Right Menu" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "EditorBackgroundParent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_ClickOffButton = { "ClickOffButton", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UEditorBackgroundParent, ClickOffButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_ClickOffButton_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_ClickOffButton_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_Width_MetaData[] = {
		{ "Category", "Right Menu" },
		{ "Comment", "/** Width of the \"right menu\". Also, (screen width - Width) is the width of the \"click off\" button (dim area). */" },
		{ "ModuleRelativePath", "EditorBackgroundParent.h" },
		{ "ToolTip", "Width of the \"right menu\". Also, (screen width - Width) is the width of the \"click off\" button (dim area)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UEditorBackgroundParent, Width), METADATA_PARAMS(Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_Width_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_Width_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEditorBackgroundParent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_ClickOffButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEditorBackgroundParent_Statics::NewProp_Width,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEditorBackgroundParent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEditorBackgroundParent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UEditorBackgroundParent_Statics::ClassParams = {
		&UEditorBackgroundParent::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UEditorBackgroundParent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UEditorBackgroundParent_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UEditorBackgroundParent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UEditorBackgroundParent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UEditorBackgroundParent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UEditorBackgroundParent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UEditorBackgroundParent, 1320679229);
	template<> GENEHUNTER_API UClass* StaticClass<UEditorBackgroundParent>()
	{
		return UEditorBackgroundParent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UEditorBackgroundParent(Z_Construct_UClass_UEditorBackgroundParent, &UEditorBackgroundParent::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UEditorBackgroundParent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEditorBackgroundParent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
