// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UType;
#ifdef GENEHUNTER_Type_generated_h
#error "Type.generated.h already included, missing '#pragma once' in Type.h"
#endif
#define GENEHUNTER_Type_generated_h

#define GeneHunter_Source_GeneHunter_Type_h_16_SPARSE_DATA
#define GeneHunter_Source_GeneHunter_Type_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetNeutralCoverage); \
	DECLARE_FUNCTION(execSortTypesDefendingRatio); \
	DECLARE_FUNCTION(execSortTypesAttackingRatio); \
	DECLARE_FUNCTION(execSortTypesDefending); \
	DECLARE_FUNCTION(execSortTypesAttacking); \
	DECLARE_FUNCTION(execGetDefendingTypesBetween); \
	DECLARE_FUNCTION(execGetImmuneToTypes); \
	DECLARE_FUNCTION(execGetNeutralDefendTypes); \
	DECLARE_FUNCTION(execGetHealedByTypes); \
	DECLARE_FUNCTION(execGetResistsTypes); \
	DECLARE_FUNCTION(execGetWeakToTypes); \
	DECLARE_FUNCTION(execGetAttackingTypesBetween); \
	DECLARE_FUNCTION(execGetNeutralAttackTypes); \
	DECLARE_FUNCTION(execGetHealsTypes); \
	DECLARE_FUNCTION(execGetZeroDamageToTypes); \
	DECLARE_FUNCTION(execGetIneffectiveAgainstTypes); \
	DECLARE_FUNCTION(execGetEffectiveAgainstTypes); \
	DECLARE_FUNCTION(execGetModifierWhenAttacked);


#define GeneHunter_Source_GeneHunter_Type_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetNeutralCoverage); \
	DECLARE_FUNCTION(execSortTypesDefendingRatio); \
	DECLARE_FUNCTION(execSortTypesAttackingRatio); \
	DECLARE_FUNCTION(execSortTypesDefending); \
	DECLARE_FUNCTION(execSortTypesAttacking); \
	DECLARE_FUNCTION(execGetDefendingTypesBetween); \
	DECLARE_FUNCTION(execGetImmuneToTypes); \
	DECLARE_FUNCTION(execGetNeutralDefendTypes); \
	DECLARE_FUNCTION(execGetHealedByTypes); \
	DECLARE_FUNCTION(execGetResistsTypes); \
	DECLARE_FUNCTION(execGetWeakToTypes); \
	DECLARE_FUNCTION(execGetAttackingTypesBetween); \
	DECLARE_FUNCTION(execGetNeutralAttackTypes); \
	DECLARE_FUNCTION(execGetHealsTypes); \
	DECLARE_FUNCTION(execGetZeroDamageToTypes); \
	DECLARE_FUNCTION(execGetIneffectiveAgainstTypes); \
	DECLARE_FUNCTION(execGetEffectiveAgainstTypes); \
	DECLARE_FUNCTION(execGetModifierWhenAttacked);


#define GeneHunter_Source_GeneHunter_Type_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUType(); \
	friend struct Z_Construct_UClass_UType_Statics; \
public: \
	DECLARE_CLASS(UType, UPrimaryDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UType)


#define GeneHunter_Source_GeneHunter_Type_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUType(); \
	friend struct Z_Construct_UClass_UType_Statics; \
public: \
	DECLARE_CLASS(UType, UPrimaryDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UType)


#define GeneHunter_Source_GeneHunter_Type_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UType(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UType) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UType); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UType); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UType(UType&&); \
	NO_API UType(const UType&); \
public:


#define GeneHunter_Source_GeneHunter_Type_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UType(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UType(UType&&); \
	NO_API UType(const UType&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UType); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UType); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UType)


#define GeneHunter_Source_GeneHunter_Type_h_16_PRIVATE_PROPERTY_OFFSET
#define GeneHunter_Source_GeneHunter_Type_h_13_PROLOG
#define GeneHunter_Source_GeneHunter_Type_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_Type_h_16_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_Type_h_16_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_Type_h_16_RPC_WRAPPERS \
	GeneHunter_Source_GeneHunter_Type_h_16_INCLASS \
	GeneHunter_Source_GeneHunter_Type_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GeneHunter_Source_GeneHunter_Type_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_Type_h_16_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_Type_h_16_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_Type_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_Type_h_16_INCLASS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_Type_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GENEHUNTER_API UClass* StaticClass<class UType>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GeneHunter_Source_GeneHunter_Type_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
