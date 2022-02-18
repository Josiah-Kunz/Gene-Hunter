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
	DEFINE_FUNCTION(UType::execSortTypesDefending)
	{
		P_GET_TARRAY(UType*,Z_Param_Types);
		P_GET_TARRAY_REF(UType*,Z_Param_Out_Sorted);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Min);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Max);
		P_GET_UBOOL(Z_Param_Inclusive);
		P_FINISH;
		P_NATIVE_BEGIN;
		UType::SortTypesDefending(Z_Param_Types,Z_Param_Out_Sorted,Z_Param_Min,Z_Param_Max,Z_Param_Inclusive);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetDefendingTypesBetween)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Min);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Max);
		P_GET_UBOOL(Z_Param_Inclusive);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetDefendingTypesBetween(Z_Param_Min,Z_Param_Max,Z_Param_Inclusive);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetImmuneToTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetImmuneToTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetNeutralDefendTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetNeutralDefendTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetHealedByTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetHealedByTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetResistsTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetResistsTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetWeakToTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetWeakToTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execSortTypesAttacking)
	{
		P_GET_TARRAY(UType*,Z_Param_Types);
		P_GET_TARRAY_REF(UType*,Z_Param_Out_Sorted);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Min);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Max);
		P_GET_UBOOL(Z_Param_Inclusive);
		P_FINISH;
		P_NATIVE_BEGIN;
		UType::SortTypesAttacking(Z_Param_Types,Z_Param_Out_Sorted,Z_Param_Min,Z_Param_Max,Z_Param_Inclusive);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetAttackingTypesBetween)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Min);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Max);
		P_GET_UBOOL(Z_Param_Inclusive);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetAttackingTypesBetween(Z_Param_Min,Z_Param_Max,Z_Param_Inclusive);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetNeutralAttackTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetNeutralAttackTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetHealsTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetHealsTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetZeroDamageToTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetZeroDamageToTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetIneffectiveAgainstTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetIneffectiveAgainstTypes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UType::execGetEffectiveAgainstTypes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UType*>*)Z_Param__Result=P_THIS->GetEffectiveAgainstTypes();
		P_NATIVE_END;
	}
	void UType::StaticRegisterNativesUType()
	{
		UClass* Class = UType::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetAttackingTypesBetween", &UType::execGetAttackingTypesBetween },
			{ "GetDefendingTypesBetween", &UType::execGetDefendingTypesBetween },
			{ "GetEffectiveAgainstTypes", &UType::execGetEffectiveAgainstTypes },
			{ "GetHealedByTypes", &UType::execGetHealedByTypes },
			{ "GetHealsTypes", &UType::execGetHealsTypes },
			{ "GetImmuneToTypes", &UType::execGetImmuneToTypes },
			{ "GetIneffectiveAgainstTypes", &UType::execGetIneffectiveAgainstTypes },
			{ "GetNeutralAttackTypes", &UType::execGetNeutralAttackTypes },
			{ "GetNeutralDefendTypes", &UType::execGetNeutralDefendTypes },
			{ "GetResistsTypes", &UType::execGetResistsTypes },
			{ "GetWeakToTypes", &UType::execGetWeakToTypes },
			{ "GetZeroDamageToTypes", &UType::execGetZeroDamageToTypes },
			{ "SortTypesAttacking", &UType::execSortTypesAttacking },
			{ "SortTypesDefending", &UType::execSortTypesDefending },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics
	{
		struct Type_eventGetAttackingTypesBetween_Parms
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Min_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetAttackingTypesBetween_Parms, Min), METADATA_PARAMS(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Min_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Min_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Max_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetAttackingTypesBetween_Parms, Max), METADATA_PARAMS(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Max_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Max_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Inclusive_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Inclusive_SetBit(void* Obj)
	{
		((Type_eventGetAttackingTypesBetween_Parms*)Obj)->Inclusive = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Inclusive = { "Inclusive", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Type_eventGetAttackingTypesBetween_Parms), &Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Inclusive_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Inclusive_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Inclusive_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetAttackingTypesBetween_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Min,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Max,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_Inclusive,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types whose damage modifiers defending this Type are between Min and Max.\n\x09 */" },
		{ "CPP_Default_Inclusive", "true" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types whose damage modifiers defending this Type are between Min and Max." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetAttackingTypesBetween", nullptr, nullptr, sizeof(Type_eventGetAttackingTypesBetween_Parms), Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetAttackingTypesBetween()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetAttackingTypesBetween_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics
	{
		struct Type_eventGetDefendingTypesBetween_Parms
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Min_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetDefendingTypesBetween_Parms, Min), METADATA_PARAMS(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Min_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Min_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Max_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetDefendingTypesBetween_Parms, Max), METADATA_PARAMS(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Max_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Max_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Inclusive_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Inclusive_SetBit(void* Obj)
	{
		((Type_eventGetDefendingTypesBetween_Parms*)Obj)->Inclusive = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Inclusive = { "Inclusive", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Type_eventGetDefendingTypesBetween_Parms), &Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Inclusive_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Inclusive_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Inclusive_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetDefendingTypesBetween_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Min,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Max,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_Inclusive,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types whose damage modifiers are between Min and Max when attacking this Type.\n\x09 */" },
		{ "CPP_Default_Inclusive", "true" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types whose damage modifiers are between Min and Max when attacking this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetDefendingTypesBetween", nullptr, nullptr, sizeof(Type_eventGetDefendingTypesBetween_Parms), Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetDefendingTypesBetween()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetDefendingTypesBetween_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics
	{
		struct Type_eventGetEffectiveAgainstTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetEffectiveAgainstTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that take increased damage from this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that take increased damage from this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetEffectiveAgainstTypes", nullptr, nullptr, sizeof(Type_eventGetEffectiveAgainstTypes_Parms), Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetEffectiveAgainstTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetEffectiveAgainstTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetHealedByTypes_Statics
	{
		struct Type_eventGetHealedByTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetHealedByTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetHealedByTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetHealedByTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetHealedByTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetHealedByTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetHealedByTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetHealedByTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 *\x09Gets Types who heal this Type instead of hurting it when attacking.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "*      Gets Types who heal this Type instead of hurting it when attacking." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetHealedByTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetHealedByTypes", nullptr, nullptr, sizeof(Type_eventGetHealedByTypes_Parms), Z_Construct_UFunction_UType_GetHealedByTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetHealedByTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetHealedByTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetHealedByTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetHealedByTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetHealedByTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetHealsTypes_Statics
	{
		struct Type_eventGetHealsTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetHealsTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetHealsTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetHealsTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetHealsTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetHealsTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetHealsTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetHealsTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that are healed instead of damaged when this Type attacks.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that are healed instead of damaged when this Type attacks." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetHealsTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetHealsTypes", nullptr, nullptr, sizeof(Type_eventGetHealsTypes_Parms), Z_Construct_UFunction_UType_GetHealsTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetHealsTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetHealsTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetHealsTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetHealsTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetHealsTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetImmuneToTypes_Statics
	{
		struct Type_eventGetImmuneToTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetImmuneToTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 *\x09Gets Types who deal zero damage to this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "*      Gets Types who deal zero damage to this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetImmuneToTypes", nullptr, nullptr, sizeof(Type_eventGetImmuneToTypes_Parms), Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetImmuneToTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetImmuneToTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics
	{
		struct Type_eventGetIneffectiveAgainstTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetIneffectiveAgainstTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that take decreased damage from this Type (not including immune or healed).\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that take decreased damage from this Type (not including immune or healed)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetIneffectiveAgainstTypes", nullptr, nullptr, sizeof(Type_eventGetIneffectiveAgainstTypes_Parms), Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics
	{
		struct Type_eventGetNeutralAttackTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetNeutralAttackTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that are damaged normally by this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that are damaged normally by this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetNeutralAttackTypes", nullptr, nullptr, sizeof(Type_eventGetNeutralAttackTypes_Parms), Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetNeutralAttackTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetNeutralAttackTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics
	{
		struct Type_eventGetNeutralDefendTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetNeutralDefendTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 *\x09Gets Types who deal neutral damage to this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "*      Gets Types who deal neutral damage to this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetNeutralDefendTypes", nullptr, nullptr, sizeof(Type_eventGetNeutralDefendTypes_Parms), Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetNeutralDefendTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetNeutralDefendTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetResistsTypes_Statics
	{
		struct Type_eventGetResistsTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetResistsTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetResistsTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetResistsTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetResistsTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetResistsTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetResistsTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetResistsTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 *\x09Gets Types who deal reduced damage to this Type, not counting zero (immune) or negative (healed by) modifiers.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "*      Gets Types who deal reduced damage to this Type, not counting zero (immune) or negative (healed by) modifiers." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetResistsTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetResistsTypes", nullptr, nullptr, sizeof(Type_eventGetResistsTypes_Parms), Z_Construct_UFunction_UType_GetResistsTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetResistsTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetResistsTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetResistsTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetResistsTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetResistsTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetWeakToTypes_Statics
	{
		struct Type_eventGetWeakToTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetWeakToTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetWeakToTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetWeakToTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetWeakToTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetWeakToTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetWeakToTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetWeakToTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 *\x09Gets Types who deal extra damage to this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "*      Gets Types who deal extra damage to this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetWeakToTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetWeakToTypes", nullptr, nullptr, sizeof(Type_eventGetWeakToTypes_Parms), Z_Construct_UFunction_UType_GetWeakToTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetWeakToTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetWeakToTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetWeakToTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetWeakToTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetWeakToTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics
	{
		struct Type_eventGetZeroDamageToTypes_Parms
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventGetZeroDamageToTypes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Gets Types that are immune to this Type.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Gets Types that are immune to this Type." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "GetZeroDamageToTypes", nullptr, nullptr, sizeof(Type_eventGetZeroDamageToTypes_Parms), Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_GetZeroDamageToTypes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_GetZeroDamageToTypes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_SortTypesAttacking_Statics
	{
		struct Type_eventSortTypesAttacking_Parms
		{
			TArray<UType*> Types;
			TArray<UType*> Sorted;
			float Min;
			float Max;
			bool Inclusive;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Types_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Types_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Types;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Sorted_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Sorted;
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
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Types_Inner = { "Types", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Types_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Types = { "Types", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesAttacking_Parms, Types), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Types_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Types_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Sorted_Inner = { "Sorted", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Sorted = { "Sorted", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesAttacking_Parms, Sorted), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Min_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesAttacking_Parms, Min), METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Min_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Min_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Max_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesAttacking_Parms, Max), METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Max_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Max_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Inclusive_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Inclusive_SetBit(void* Obj)
	{
		((Type_eventSortTypesAttacking_Parms*)Obj)->Inclusive = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Inclusive = { "Inclusive", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Type_eventSortTypesAttacking_Parms), &Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Inclusive_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Inclusive_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Inclusive_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_SortTypesAttacking_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Types_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Types,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Sorted_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Sorted,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Min,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Max,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesAttacking_Statics::NewProp_Inclusive,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesAttacking_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Sorts the given Types by the number of AttackModifiers within the specified range. For example, if Water is only good attacking against Fire, it would be near the end of the list.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Sorts the given Types by the number of AttackModifiers within the specified range. For example, if Water is only good attacking against Fire, it would be near the end of the list." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_SortTypesAttacking_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "SortTypesAttacking", nullptr, nullptr, sizeof(Type_eventSortTypesAttacking_Parms), Z_Construct_UFunction_UType_SortTypesAttacking_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesAttacking_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_SortTypesAttacking()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_SortTypesAttacking_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UType_SortTypesDefending_Statics
	{
		struct Type_eventSortTypesDefending_Parms
		{
			TArray<UType*> Types;
			TArray<UType*> Sorted;
			float Min;
			float Max;
			bool Inclusive;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Types_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Types_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Types;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Sorted_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Sorted;
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
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Types_Inner = { "Types", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Types_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Types = { "Types", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesDefending_Parms, Types), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Types_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Types_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Sorted_Inner = { "Sorted", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UType_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Sorted = { "Sorted", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesDefending_Parms, Sorted), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Min_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesDefending_Parms, Min), METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Min_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Min_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Max_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Type_eventSortTypesDefending_Parms, Max), METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Max_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Max_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Inclusive_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Inclusive_SetBit(void* Obj)
	{
		((Type_eventSortTypesDefending_Parms*)Obj)->Inclusive = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Inclusive = { "Inclusive", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Type_eventSortTypesDefending_Parms), &Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Inclusive_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Inclusive_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Inclusive_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UType_SortTypesDefending_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Types_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Types,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Sorted_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Sorted,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Min,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Max,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UType_SortTypesDefending_Statics::NewProp_Inclusive,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UType_SortTypesDefending_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/*\n\x09 * Sorts the given Types by the number of defensible Types within the specified range. For example, if Fire is only weak (defending) to Water, it would be near the end of the list.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* Sorts the given Types by the number of defensible Types within the specified range. For example, if Fire is only weak (defending) to Water, it would be near the end of the list." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UType_SortTypesDefending_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UType, nullptr, "SortTypesDefending", nullptr, nullptr, sizeof(Type_eventSortTypesDefending_Parms), Z_Construct_UFunction_UType_SortTypesDefending_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesDefending_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UType_SortTypesDefending_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UType_SortTypesDefending_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UType_SortTypesDefending()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UType_SortTypesDefending_Statics::FuncParams);
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
		{ &Z_Construct_UFunction_UType_GetAttackingTypesBetween, "GetAttackingTypesBetween" }, // 824106841
		{ &Z_Construct_UFunction_UType_GetDefendingTypesBetween, "GetDefendingTypesBetween" }, // 3753111702
		{ &Z_Construct_UFunction_UType_GetEffectiveAgainstTypes, "GetEffectiveAgainstTypes" }, // 3229038438
		{ &Z_Construct_UFunction_UType_GetHealedByTypes, "GetHealedByTypes" }, // 2317098960
		{ &Z_Construct_UFunction_UType_GetHealsTypes, "GetHealsTypes" }, // 241998324
		{ &Z_Construct_UFunction_UType_GetImmuneToTypes, "GetImmuneToTypes" }, // 158402019
		{ &Z_Construct_UFunction_UType_GetIneffectiveAgainstTypes, "GetIneffectiveAgainstTypes" }, // 378120126
		{ &Z_Construct_UFunction_UType_GetNeutralAttackTypes, "GetNeutralAttackTypes" }, // 390245405
		{ &Z_Construct_UFunction_UType_GetNeutralDefendTypes, "GetNeutralDefendTypes" }, // 3236279236
		{ &Z_Construct_UFunction_UType_GetResistsTypes, "GetResistsTypes" }, // 4088717649
		{ &Z_Construct_UFunction_UType_GetWeakToTypes, "GetWeakToTypes" }, // 843383500
		{ &Z_Construct_UFunction_UType_GetZeroDamageToTypes, "GetZeroDamageToTypes" }, // 3199654397
		{ &Z_Construct_UFunction_UType_SortTypesAttacking, "SortTypesAttacking" }, // 3168246668
		{ &Z_Construct_UFunction_UType_SortTypesDefending, "SortTypesDefending" }, // 2727897269
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
		{ "Comment", "/*\n\x09 * An array of LinearColors associated with this Type to do with as you please. For example, the zeroth color can be associated with a background color.\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* An array of LinearColors associated with this Type to do with as you please. For example, the zeroth color can be associated with a background color." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UType_Statics::NewProp_Colors = { "Colors", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UType, Colors), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UType_Statics::NewProp_Colors_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UType_Statics::NewProp_Colors_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UType_Statics::NewProp_SupportingText_MetaData[] = {
		{ "Category", "Type" },
		{ "Comment", "/*\n\x09 * The Text that describes this Type (e.g., dev note, flavor text, etc.).\n\x09 */" },
		{ "ModuleRelativePath", "Type.h" },
		{ "ToolTip", "* The Text that describes this Type (e.g., dev note, flavor text, etc.)." },
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
	IMPLEMENT_CLASS(UType, 334238826);
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
