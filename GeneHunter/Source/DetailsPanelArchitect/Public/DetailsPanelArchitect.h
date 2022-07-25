#pragma once

#include "CoreUObject.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditor/Public/PropertyEditorModule.h"
#include "DetailsPanelArchitect/Public/FDPAButton.h"
#include "DPAButtonDrawer.h"

class FDPAModule : public IModuleInterface{

#pragma region Overrides
	
public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

#pragma endregion

#pragma region Macros

/*
#define DPA_BUTTON(Cat, ...) \
	UPROPERTY(EditAnywhere, Category = Cat) \
	FDPAButton Button##__LINE__ = FDPAButton(##__VA_ARGS__)
*/
#pragma endregion
	
};