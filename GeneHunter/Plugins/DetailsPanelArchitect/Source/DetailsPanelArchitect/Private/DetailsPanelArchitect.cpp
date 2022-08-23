// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetailsPanelArchitect.h"

#include "AffinitiesComponent.h"
#include "AffinitiesComponentDrawer.h"
#include "StatsComponent.h"
#include "StatsComponentDrawer.h"

#define LOCTEXT_NAMESPACE "FDetailsPanelArchitectModule"

void FDetailsPanelArchitectModule::StartupModule()
{
	
	// Say hello
	UE_LOG(LogTemp, Display, TEXT("DetailsPanelArchitect loaded. Hello! =)"))

	// Get module
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	// Register the specific custom class layouts (based on their names, e.g., StatsComponent and StatsComponentDrawer)
	PropertyEdModule.RegisterCustomClassLayout(
		UStatsComponent::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(StatsComponentDrawer::MakeInstance)
	);
	PropertyEdModule.RegisterCustomClassLayout(
		UAffinitiesComponent::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(AffinitiesComponentDrawer::MakeInstance)
	);
}

void FDetailsPanelArchitectModule::ShutdownModule()
{

	// Say bye
	UE_LOG(LogTemp, Display, TEXT("DetailsPanelArchitect unloaded. Goodbye =("))

	// Get module
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	// Unregister
	PropertyEdModule.UnregisterCustomClassLayout(UStatsComponent::StaticClass()->GetFName());
	PropertyEdModule.UnregisterCustomClassLayout(UAffinitiesComponent::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDetailsPanelArchitectModule, DetailsPanelArchitect)