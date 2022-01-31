// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/EditableTextPlus.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEditableTextPlus() {}
// Cross Module References
	GENEHUNTER_API UClass* Z_Construct_UClass_UEditableTextPlus_NoRegister();
	GENEHUNTER_API UClass* Z_Construct_UClass_UEditableTextPlus();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
	UMG_API UClass* Z_Construct_UClass_UWidget_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UEditableTextPlus::execSynchronizeProperty)
	{
		P_GET_OBJECT(UWidget,Z_Param_Widget);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SynchronizeProperty(Z_Param_Widget);
		P_NATIVE_END;
	}
	static FName NAME_UEditableTextPlus_OnSynchronizeProperties = FName(TEXT("OnSynchronizeProperties"));
	void UEditableTextPlus::OnSynchronizeProperties()
	{
		ProcessEvent(FindFunctionChecked(NAME_UEditableTextPlus_OnSynchronizeProperties),NULL);
	}
	void UEditableTextPlus::StaticRegisterNativesUEditableTextPlus()
	{
		UClass* Class = UEditableTextPlus::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SynchronizeProperty", &UEditableTextPlus::execSynchronizeProperty },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties_Statics::Function_MetaDataParams[] = {
		{ "Category", "User Interface" },
		{ "Comment", "/**\n\x09 * This is called after a widget is constructed and properties are synchronized.\n\x09 * It can also be called by the editor to update modified state.\n\x09 * Override this event in blueprint to update the widget after a default \n\x09 * property is modified.\n\x09 */" },
		{ "ModuleRelativePath", "EditableTextPlus.h" },
		{ "ToolTip", "This is called after a widget is constructed and properties are synchronized.\nIt can also be called by the editor to update modified state.\nOverride this event in blueprint to update the widget after a default\nproperty is modified." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEditableTextPlus, nullptr, "OnSynchronizeProperties", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics
	{
		struct EditableTextPlus_eventSynchronizeProperty_Parms
		{
			UWidget* Widget;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Widget_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Widget;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::NewProp_Widget_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::NewProp_Widget = { "Widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(EditableTextPlus_eventSynchronizeProperty_Parms, Widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::NewProp_Widget_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::NewProp_Widget_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::NewProp_Widget,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::Function_MetaDataParams[] = {
		{ "Category", "User Interface" },
		{ "ModuleRelativePath", "EditableTextPlus.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UEditableTextPlus, nullptr, "SynchronizeProperty", nullptr, nullptr, sizeof(EditableTextPlus_eventSynchronizeProperty_Parms), Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UEditableTextPlus_NoRegister()
	{
		return UEditableTextPlus::StaticClass();
	}
	struct Z_Construct_UClass_UEditableTextPlus_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UEditableTextPlus_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_GeneHunter,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UEditableTextPlus_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UEditableTextPlus_OnSynchronizeProperties, "OnSynchronizeProperties" }, // 257438328
		{ &Z_Construct_UFunction_UEditableTextPlus_SynchronizeProperty, "SynchronizeProperty" }, // 2917750028
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UEditableTextPlus_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "EditableTextPlus.h" },
		{ "ModuleRelativePath", "EditableTextPlus.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UEditableTextPlus_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEditableTextPlus>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UEditableTextPlus_Statics::ClassParams = {
		&UEditableTextPlus::StaticClass,
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
		0x00B010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UEditableTextPlus_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UEditableTextPlus_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UEditableTextPlus()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UECodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UEditableTextPlus_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UEditableTextPlus, 1201732072);
	template<> GENEHUNTER_API UClass* StaticClass<UEditableTextPlus>()
	{
		return UEditableTextPlus::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UEditableTextPlus(Z_Construct_UClass_UEditableTextPlus, &UEditableTextPlus::StaticClass, TEXT("/Script/GeneHunter"), TEXT("UEditableTextPlus"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UEditableTextPlus);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
