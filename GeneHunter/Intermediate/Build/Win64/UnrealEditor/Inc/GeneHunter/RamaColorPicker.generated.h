// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLinearColor;
#ifdef GENEHUNTER_RamaColorPicker_generated_h
#error "RamaColorPicker.generated.h already included, missing '#pragma once' in RamaColorPicker.h"
#endif
#define GENEHUNTER_RamaColorPicker_generated_h

#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_14_DELEGATE \
struct _Script_GeneHunter_eventOnJoyColorChangedEvent_Parms \
{ \
	FLinearColor NewColor; \
}; \
static inline void FOnJoyColorChangedEvent_DelegateWrapper(const FMulticastScriptDelegate& OnJoyColorChangedEvent, FLinearColor const& NewColor) \
{ \
	_Script_GeneHunter_eventOnJoyColorChangedEvent_Parms Parms; \
	Parms.NewColor=NewColor; \
	OnJoyColorChangedEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_SPARSE_DATA
#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetJoyColor);


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetJoyColor);


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURamaColorPicker(); \
	friend struct Z_Construct_UClass_URamaColorPicker_Statics; \
public: \
	DECLARE_CLASS(URamaColorPicker, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(URamaColorPicker)


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_INCLASS \
private: \
	static void StaticRegisterNativesURamaColorPicker(); \
	friend struct Z_Construct_UClass_URamaColorPicker_Statics; \
public: \
	DECLARE_CLASS(URamaColorPicker, UWidget, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GeneHunter"), NO_API) \
	DECLARE_SERIALIZER(URamaColorPicker)


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URamaColorPicker(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URamaColorPicker) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URamaColorPicker); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URamaColorPicker); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URamaColorPicker(URamaColorPicker&&); \
	NO_API URamaColorPicker(const URamaColorPicker&); \
public:


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URamaColorPicker(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API URamaColorPicker(URamaColorPicker&&); \
	NO_API URamaColorPicker(const URamaColorPicker&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URamaColorPicker); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URamaColorPicker); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URamaColorPicker)


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_PRIVATE_PROPERTY_OFFSET
#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_19_PROLOG
#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_RPC_WRAPPERS \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_INCLASS \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_PRIVATE_PROPERTY_OFFSET \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_SPARSE_DATA \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_INCLASS_NO_PURE_DECLS \
	GeneHunter_Source_GeneHunter_RamaColorPicker_h_22_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class RamaColorPicker."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GENEHUNTER_API UClass* StaticClass<class URamaColorPicker>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID GeneHunter_Source_GeneHunter_RamaColorPicker_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
