#pragma once

class FDetailsPanelArchitect : public IModuleInterface{

public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
	
};