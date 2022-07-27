#pragma once

#include "CoreUObject.h"
#include "Modules/ModuleManager.h"
#include "GeneHunter/StatsBlock/StatsBlock.h"
#include "PropertyEditor/Public/PropertyEditorModule.h"
#include "StatsBlockDetails.h"

class FGeneHunterEditorModule : public IModuleInterface{

public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
	
};