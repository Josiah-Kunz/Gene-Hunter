// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UType;
struct FAssetData;
class UObject;
#ifdef GENEHUNTER_GeneHunterBPLibrary_generated_h
#error "GeneHunterBPLibrary.generated.h already included, missing '#pragma once' in GeneHunterBPLibrary.h"
#endif
#define GENEHUNTER_GeneHunterBPLibrary_generated_h

#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_SPARSE_DATA
#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetAllTypes); \
	DECLARE_FUNCTION(execGetAllTypeAssets); \
	DECLARE_FUNCTION(execPruneTypeAttackMods); \
	DECLARE_FUNCTION(execSaveLoadedAssetFromAnywhere); \
	DECLARE_FUNCTION(execSortAssetsAlphabetically); \
	DECLARE_FUNCTION(execEnsureValidAssetName);


#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetAllTypes); \
	DECLARE_FUNCTION(execGetAllTypeAssets); \
	DECLARE_FUNCTION(execPruneTypeAttackMods); \
	DECLARE_FUNCTION(execSaveLoadedAssetFromAnywhere); \
	DECLARE_FUNCTION(execSortAssetsAlphabetically); \
	DECLARE_FUNCTION(execEnsureValidAssetName);


#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGeneHunterBPLibrary(); \
	friend struct Z_Construct_UClass_UGeneHunterBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UGeneHunterBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UGeneHunterBPLibrary)


#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_INCLASS \
private: \
	static void StaticRegisterNativesUGeneHunterBPLibrary(); \
	friend struct Z_Construct_UClass_UGeneHunterBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UGeneHunterBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UGeneHunterBPLibrary)


#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGeneHunterBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGeneHunterBPLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGeneHunterBPLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGeneHunterBPLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGeneHunterBPLibrary(UGeneHunterBPLibrary&&); \
	NO_API UGeneHunterBPLibrary(const UGeneHunterBPLibrary&); \
public:


#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGeneHunterBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGeneHunterBPLibrary(UGeneHunterBPLibrary&&); \
	NO_API UGeneHunterBPLibrary(const UGeneHunterBPLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGeneHunterBPLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGeneHunterBPLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGeneHunterBPLibrary)


#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_PRIVATE_PROPERTY_OFFSET
#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_16_PROLOG
#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_RPC_WRAPPERS \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_INCLASS \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_INCLASS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GENEHUNTER_API UClass* StaticClass<class UGeneHunterBPLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GeneHunter_Source_GeneHunter_GeneHunterBPLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
