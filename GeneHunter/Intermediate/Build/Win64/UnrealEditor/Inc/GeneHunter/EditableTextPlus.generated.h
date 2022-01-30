// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GENEHUNTER_EditableTextPlus_generated_h
#error "EditableTextPlus.generated.h already included, missing '#pragma once' in EditableTextPlus.h"
#endif
#define GENEHUNTER_EditableTextPlus_generated_h

#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_31_DELEGATE \
struct EditableTextPlus_eventOnEditableTextCommittedEvent_Parms \
{ \
	FText Text; \
	TEnumAsByte<ETextCommit::Type> CommitMethod; \
}; \
static inline void FOnEditableTextCommittedEvent_DelegateWrapper(const FMulticastScriptDelegate& OnEditableTextCommittedEvent, FText const& Text, ETextCommit::Type CommitMethod) \
{ \
	EditableTextPlus_eventOnEditableTextCommittedEvent_Parms Parms; \
	Parms.Text=Text; \
	Parms.CommitMethod=CommitMethod; \
	OnEditableTextCommittedEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_30_DELEGATE \
struct EditableTextPlus_eventOnEditableTextChangedEvent_Parms \
{ \
	FText Text; \
}; \
static inline void FOnEditableTextChangedEvent_DelegateWrapper(const FMulticastScriptDelegate& OnEditableTextChangedEvent, FText const& Text) \
{ \
	EditableTextPlus_eventOnEditableTextChangedEvent_Parms Parms; \
	Parms.Text=Text; \
	OnEditableTextChangedEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_SPARSE_DATA
#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetJustification); \
	DECLARE_FUNCTION(execSetIsReadOnly); \
	DECLARE_FUNCTION(execSetHintText); \
	DECLARE_FUNCTION(execSetIsPassword); \
	DECLARE_FUNCTION(execSetText); \
	DECLARE_FUNCTION(execGetText);


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetJustification); \
	DECLARE_FUNCTION(execSetIsReadOnly); \
	DECLARE_FUNCTION(execSetHintText); \
	DECLARE_FUNCTION(execSetIsPassword); \
	DECLARE_FUNCTION(execSetText); \
	DECLARE_FUNCTION(execGetText);


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEditableTextPlus(); \
	friend struct Z_Construct_UClass_UEditableTextPlus_Statics; \
public: \
	DECLARE_CLASS(UEditableTextPlus, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UEditableTextPlus)


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_INCLASS \
private: \
	static void StaticRegisterNativesUEditableTextPlus(); \
	friend struct Z_Construct_UClass_UEditableTextPlus_Statics; \
public: \
	DECLARE_CLASS(UEditableTextPlus, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(UEditableTextPlus)


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_STANDARD_CONSTRUCTORS \
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


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_ENHANCED_CONSTRUCTORS \
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


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_PRIVATE_PROPERTY_OFFSET
#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_23_PROLOG
#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_RPC_WRAPPERS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_INCLASS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_INCLASS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_EditableTextPlus_h_26_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class EditableTextPlus."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GENEHUNTER_API UClass* StaticClass<class UEditableTextPlus>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GeneHunter_Source_GeneHunter_EditableTextPlus_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
