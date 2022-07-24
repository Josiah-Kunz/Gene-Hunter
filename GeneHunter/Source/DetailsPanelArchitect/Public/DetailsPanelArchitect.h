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
	
};