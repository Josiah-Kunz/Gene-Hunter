#include "GeneHunterEditor.h"

void FGeneHunterEditorModule::StartupModule()
{

	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
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