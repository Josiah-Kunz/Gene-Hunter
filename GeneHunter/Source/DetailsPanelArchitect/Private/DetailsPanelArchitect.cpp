#include "DetailsPanelArchitect.h"

#include "StatsComponent.h"
#include "StatsComponentDrawer.h"

void FDetailsPanelArchitect::StartupModule()
{

	// Get module
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// Register the specific custom class layouts (based on their names, e.g., UStatsBlock and FStatsBlockDetails)
	PropertyEdModule.RegisterCustomClassLayout(
		UStatsComponent::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(StatsComponentDrawer::MakeInstance)
		);
	
	UE_LOG(LogTemp, Warning, TEXT("DetailsPanelArchitect loaded! HELLO! =)"))
}

void FDetailsPanelArchitect::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("DetailsPanelArchitect unloaded---bye =("))
}
