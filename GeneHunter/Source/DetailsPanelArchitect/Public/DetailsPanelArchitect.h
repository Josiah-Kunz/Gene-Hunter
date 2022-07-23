#pragma once

#include "CoreUObject.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditor/Public/PropertyEditorModule.h"
#include "DetailsPanelArchitect/Public/DPAButton.h"
#include "DPAButtonDrawer.h"

class FDPAModule : public IModuleInterface{

public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
	
};