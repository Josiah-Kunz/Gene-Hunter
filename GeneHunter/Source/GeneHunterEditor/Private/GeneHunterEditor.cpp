#include "GeneHunterEditor.h"

void FGeneHunterEditorModule::StartupModule()
{

	// Get module
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// Register the specific custom class layouts (based on their names, e.g., UStatsBlock and FStatsBlockDetails)
	PropertyEdModule.RegisterCustomClassLayout(
		UStatsBlock::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(FStatsBlockDetails::MakeInstance)
		);
	
	UE_LOG(LogTemp, Warning, TEXT("GeneHunterEditor loaded!"))
}

void FGeneHunterEditorModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("GeneHunterEditor unloaded!"))
}

IMPLEMENT_MODULE(FGeneHunterEditorModule, GeneHunterEditor);