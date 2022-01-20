// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GeneHunter/TypeAdvantageEditorEnums.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTypeAdvantageEditorEnums() {}
// Cross Module References
	GENEHUNTER_API UEnum* Z_Construct_UEnum_GeneHunter_TAText();
	UPackage* Z_Construct_UPackage__Script_GeneHunter();
	GENEHUNTER_API UEnum* Z_Construct_UEnum_GeneHunter_TAQueueStatus();
// End Cross Module References
	static UEnum* TAText_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_GeneHunter_TAText, Z_Construct_UPackage__Script_GeneHunter(), TEXT("TAText"));
		}
		return Singleton;
	}
	template<> GENEHUNTER_API UEnum* StaticEnum<TAText>()
	{
		return TAText_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_TAText(TAText_StaticEnum, TEXT("/Script/GeneHunter"), TEXT("TAText"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_GeneHunter_TAText_Hash() { return 4150020647U; }
	UEnum* Z_Construct_UEnum_GeneHunter_TAText()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_GeneHunter();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("TAText"), 0, Get_Z_Construct_UEnum_GeneHunter_TAText_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UECodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "TAText::DevNote", (int64)TAText::DevNote },
				{ "TAText::Description", (int64)TAText::Description },
				{ "TAText::FlavorText", (int64)TAText::FlavorText },
			};
#if WITH_METADATA
			const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Description.DisplayName", "Description" },
				{ "Description.Name", "TAText::Description" },
				{ "DevNote.DisplayName", "DevNote" },
				{ "DevNote.Name", "TAText::DevNote" },
				{ "FlavorText.DisplayName", "FlavorText" },
				{ "FlavorText.Name", "TAText::FlavorText" },
				{ "ModuleRelativePath", "TypeAdvantageEditorEnums.h" },
			};
#endif
			static const UECodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_GeneHunter,
				nullptr,
				"TAText",
				"TAText",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UECodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UECodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* TAQueueStatus_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_GeneHunter_TAQueueStatus, Z_Construct_UPackage__Script_GeneHunter(), TEXT("TAQueueStatus"));
		}
		return Singleton;
	}
	template<> GENEHUNTER_API UEnum* StaticEnum<TAQueueStatus>()
	{
		return TAQueueStatus_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_TAQueueStatus(TAQueueStatus_StaticEnum, TEXT("/Script/GeneHunter"), TEXT("TAQueueStatus"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_GeneHunter_TAQueueStatus_Hash() { return 825984613U; }
	UEnum* Z_Construct_UEnum_GeneHunter_TAQueueStatus()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_GeneHunter();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("TAQueueStatus"), 0, Get_Z_Construct_UEnum_GeneHunter_TAQueueStatus_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UECodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "TAQueueStatus::Idle", (int64)TAQueueStatus::Idle },
				{ "TAQueueStatus::Rename", (int64)TAQueueStatus::Rename },
			};
#if WITH_METADATA
			const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Idle.DisplayName", "Idle" },
				{ "Idle.Name", "TAQueueStatus::Idle" },
				{ "ModuleRelativePath", "TypeAdvantageEditorEnums.h" },
				{ "Rename.DisplayName", "Rename" },
				{ "Rename.Name", "TAQueueStatus::Rename" },
			};
#endif
			static const UECodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_GeneHunter,
				nullptr,
				"TAQueueStatus",
				"TAQueueStatus",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UECodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UECodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
