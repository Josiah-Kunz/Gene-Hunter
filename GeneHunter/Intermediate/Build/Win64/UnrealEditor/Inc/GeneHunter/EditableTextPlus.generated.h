// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLinearColor;
#ifdef GENEHUNTER_EditableTextPlus_generated_h
#error "EditableTextPlus.generated.h already included, missing '#pragma once' in EditableTextPlus.h"
#endif
#define GENEHUNTER_EditableTextPlus_generated_h

#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_11_DELEGATE \
struct _Script_GeneHunter_eventOnEditableTextChangedInteractiveEvent_Parms \
{ \
	FText NewText; \
}; \
static inline void FOnEditableTextChangedInteractiveEvent_DelegateWrapper(const FMulticastScriptDelegate& OnEditableTextChangedInteractiveEvent, FText const& NewText) \
{ \
	_Script_GeneHunter_eventOnEditableTextChangedInteractiveEvent_Parms Parms; \
	Parms.NewText=NewText; \
	OnEditableTextChangedInteractiveEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_10_DELEGATE \
struct _Script_GeneHunter_eventOnEditableTextChangedProgrammaticEvent_Parms \
{ \
	FText NewText; \
}; \
static inline void FOnEditableTextChangedProgrammaticEvent_DelegateWrapper(const FMulticastScriptDelegate& OnEditableTextChangedProgrammaticEvent, FText const& NewText) \
{ \
	_Script_GeneHunter_eventOnEditableTextChangedProgrammaticEvent_Parms Parms; \
	Parms.NewText=NewText; \
	OnEditableTextChangedProgrammaticEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_SPARSE_DATA
#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetFontColor); \
	DECLARE_FUNCTION(execSetTextByUser); \
	DECLARE_FUNCTION(execSetTextInteractive); \
	DECLARE_FUNCTION(execSetTextByCode); \
	DECLARE_FUNCTION(execSetTextProgrammatic);


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetFontColor); \
	DECLARE_FUNCTION(execSetTextByUser); \
	DECLARE_FUNCTION(execSetTextInteractive); \
	DECLARE_FUNCTION(execSetTextByCode); \
	DECLARE_FUNCTION(execSetTextProgrammatic);


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEditableTextPlus(); \
	friend struct Z_Construct_UClass_UEditableTextPlus_Statics; \
public: \
	DECLARE_CLASS(UEditableTextPlus, UEditableText, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UEditableTextPlus)


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_INCLASS \
private: \
	static void StaticRegisterNativesUEditableTextPlus(); \
	friend struct Z_Construct_UClass_UEditableTextPlus_Statics; \
public: \
	DECLARE_CLASS(UEditableTextPlus, UEditableText, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UEditableTextPlus)


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEditableTextPlus(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEditableTextPlus) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEditableTextPlus); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEditableTextPlus); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UEditableTextPlus(UEditableTextPlus&&); \
	NO_API UEditableTextPlus(const UEditableTextPlus&); \
public:


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UEditableTextPlus(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UEditableTextPlus(UEditableTextPlus&&); \
	NO_API UEditableTextPlus(const UEditableTextPlus&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEditableTextPlus); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEditableTextPlus); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UEditableTextPlus)


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_PRIVATE_PROPERTY_OFFSET
#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_16_PROLOG
#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_RPC_WRAPPERS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_INCLASS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_INCLASS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GENEHUNTER_API UClass* StaticClass<class UEditableTextPlus>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GeneHunter_Source_GeneHunter_EditableTextPlus_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
