// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetailsPanelArchitect.h"

#include "AffinitiesComponent.h"
#include "AffinitiesComponentDrawer.h"
#include "LevelComponentDrawer.h"
#include "StatsComponent.h"
#include "StatsComponentDrawer.h"

#define LOCTEXT_NAMESPACE "FDetailsPanelArchitectModule"

#define REGISTER_CLASS(NonUName) \
	PropertyEdModule.RegisterCustomClassLayout( \
		U##NonUName##::StaticClass()->GetFName(), \
		FOnGetDetailCustomizationInstance::CreateStatic( NonUName##Drawer::MakeInstance) \
	);

#define UNREGISTER_CLASS(NonUName) \
	PropertyEdModule.UnregisterCustomClassLayout( U##NonUName##::StaticClass()->GetFName());


void FDetailsPanelArchitectModule::StartupModule()
{
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	REGISTER_CLASS(AffinitiesComponent)
	REGISTER_CLASS(StatsComponent)
	REGISTER_CLASS(LevelComponent)
}

void FDetailsPanelArchitectModule::ShutdownModule() \
{ 
	UE_LOG(LogTemp, Display, TEXT("DetailsPanelArchitect unloaded. Goodbye =(")) 
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor"); 

	UNREGISTER_CLASS(AffinitiesComponent)
	UNREGISTER_CLASS(StatsComponent)
	UNREGISTER_CLASS(LevelComponent)
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDetailsPanelArchitectModule, DetailsPanelArchitect)