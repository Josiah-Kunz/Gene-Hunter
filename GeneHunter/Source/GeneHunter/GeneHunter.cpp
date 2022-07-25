// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneHunter.h"
#include "Modules/ModuleManager.h"

void FGeneHunterModule::StartupModule()
{

	// Get module
	FPropertyEditorModule& PropertyEdModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// Register the specific custom class layouts (based on their names, e.g., UStatsBlock and FStatsBlockDetails)
	/*PropertyEdModule.RegisterCustomClassLayout(
		UStatsBlock::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(FStatsBlockDetails::MakeInstance)
		);*/
	
	UE_LOG(LogTemp, Display, TEXT("GeneHunter loaded! HELLO! =)"))
}

void FGeneHunterModule::ShutdownModule()
{
	UE_LOG(LogTemp, Display, TEXT("GeneHunter unloaded---bye =("))
}

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, GeneHunter, "GeneHunter" );

