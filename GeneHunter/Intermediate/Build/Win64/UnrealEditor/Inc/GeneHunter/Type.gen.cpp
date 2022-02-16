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
	DEFINE_FUNCTION(UType::execGetDamageTypesBetween)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Min);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Max);
		P_GET_UBOOL(Z_Param_Inclusive);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetDamageTypesBetween(Z_Param_Min,Z_Param_Max,Z_Param_Inclusive);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetNeutralDamageTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetNeutralDamageTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetHealedDamageTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetHealedDamageTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetImmuneTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetImmuneTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetDecreasedDamageTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetDecreasedDamageTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetIncreasedDamageTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetIncreasedDamageTypes();
		P_NATIVE_END;
	}
	void UType::StaticRegisterNativesUType()
	{
		UClass* Class = UType::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetDamageTypesBetween", &UType::execGetDamageTypesBetween },
			{ "GetDecreasedDamageTypes", &UType::execGetDecreasedDamageTypes },
			{ "GetHealedDamageTypes", &UType::execGetHealedDamageTypes },
			{ "GetImmuneTypes", &UType::execGetImmuneTypes },
			{ "GetIncreasedDamageTypes", &UType::execGetIncreasedDamageTypes },
			{ "GetNeutralDamageTypes", &UType::execGetNeutralDamageTypes },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics
	{
		struct Type_eventGetDamageTypesBetween_Parms
		{
			float Min;
			float Max;
			bool Inclusive;
			TArray<UType*> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Min_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Min;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Max_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Max;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Inclusive_MetaData[];
#endif
		static void NewProp_Inclusive_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_Inclusive;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Min_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetDamageTypesBetween_Parms, Min), METADATA_PARAMS(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Min_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Min_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Max_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetDamageTypesBetween_Parms, Max), METADATA_PARAMS(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Max_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Max_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Inclusive_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Inclusive_SetBit(void* Obj)
	{
		((Type_eventGetDamageTypesBetween_Parms*)Obj)->Inclusive = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Inclusive = { "Inclusive", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Type_eventGetDamageTypesBetween_Parms), &Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Inclusive_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Inclusive_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Inclusive_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetDamageTypesBetween_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Min,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Max,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_Inclusive,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types whose damage modifiers are between Min and Max for this Type.\n\x09 */" },
		{ "CPP_Default_Inclusive", "true" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types whose damage modifiers are between Min and Max for this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetDamageTypesBetween", nullptr, nullptr, sizeof(Type_eventGetDamageTypesBetween_Parms), Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetDamageTypesBetween()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetDamageTypesBetween_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics
	{
		struct Type_eventGetDecreasedDamageTypes_Parms
		{
			TArray<UType*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetDecreasedDamageTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that take decreased damage from this Type (not including immune or healed).\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that take decreased damage from this Type (not including immune or healed)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetDecreasedDamageTypes", nullptr, nullptr, sizeof(Type_eventGetDecreasedDamageTypes_Parms), Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetDecreasedDamageTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetDecreasedDamageTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics
	{
		struct Type_eventGetHealedDamageTypes_Parms
		{
			TArray<UType*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetHealedDamageTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that are healed instead of damaged when this Type attacks.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that are healed instead of damaged when this Type attacks." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetHealedDamageTypes", nullptr, nullptr, sizeof(Type_eventGetHealedDamageTypes_Parms), Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetHealedDamageTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetHealedDamageTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetImmuneTypes_Statics
	{
		struct Type_eventGetImmuneTypes_Parms
		{
			TArray<UType*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetImmuneTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetImmuneTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetImmuneTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetImmuneTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetImmuneTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetImmuneTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetImmuneTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that are immune to this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that are immune to this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetImmuneTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetImmuneTypes", nullptr, nullptr, sizeof(Type_eventGetImmuneTypes_Parms), Z_Construct_UFunction_UType_GetImmuneTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetImmuneTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetImmuneTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetImmuneTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetImmuneTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetImmuneTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics
	{
		struct Type_eventGetIncreasedDamageTypes_Parms
		{
			TArray<UType*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetIncreasedDamageTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that take increased damage from this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that take increased damage from this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetIncreasedDamageTypes", nullptr, nullptr, sizeof(Type_eventGetIncreasedDamageTypes_Parms), Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetIncreasedDamageTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetIncreasedDamageTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics
	{
		struct Type_eventGetNeutralDamageTypes_Parms
		{
			TArray<UType*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetNeutralDamageTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that are damaged normally by this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that are damaged normally by this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetNeutralDamageTypes", nullptr, nullptr, sizeof(Type_eventGetNeutralDamageTypes_Parms), Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetNeutralDamageTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetNeutralDamageTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UType_NoRegister()
	{
		return UType::StaticClass();
	}
	struct Z_Construct_UClass_UType_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
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
	const FClassFunctionLinkInfo Z_Construct_UClass_UType_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UType_GetDamageTypesBetween, "GetDamageTypesBetween" }, // 3598934823
		{ &Z_Construct_UFunction_UType_GetDecreasedDamageTypes, "GetDecreasedDamageTypes" }, // 2853787387
		{ &Z_Construct_UFunction_UType_GetHealedDamageTypes, "GetHealedDamageTypes" }, // 2248207427
		{ &Z_Construct_UFunction_UType_GetImmuneTypes, "GetImmuneTypes" }, // 595030097
		{ &Z_Construct_UFunction_UType_GetIncreasedDamageTypes, "GetIncreasedDamageTypes" }, // 2035637466
		{ &Z_Construct_UFunction_UType_GetNeutralDamageTypes, "GetNeutralDamageTypes" }, // 1688982370
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
		FuncInfo,
		Z_Construct_UClass_UType_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
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
	IMPLEMENT_CLASS(UType, 3393077111);
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
