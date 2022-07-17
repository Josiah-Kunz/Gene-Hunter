#include "DetailsPanelArchitect.h"

void FDPAModule::StartupModule()
{

	// Get module
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// Register the specific custom class layouts (based on their names, e.g., UStatsBlock and FStatsBlockDetails)
	/*PropertyEdModule.RegisterCustomClassLayout(
		UStatsBlock::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(FStatsBlockDetails::MakeInstance)
		);*/
	
	UE_LOG(LogTemp, Display, TEXT("DetailsPanelArchitect loaded! HELLO! =)"))
}

void FDPAModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("DetailsPanelArchitect unloaded---bye =("))
}

IMPLEMENT_MODULE(FDPAModule, DetailsPanelArchitect);