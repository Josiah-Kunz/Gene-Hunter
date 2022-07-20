// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DetailsPanelArchitect : ModuleRules 
{
	public DetailsPanelArchitect(ReadOnlyTargetRules Target) : base(Target){

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


		PublicIncludePaths.Add("DetailsPanelArchitect/Public");
		PrivateIncludePaths.Add("DetailsPanelArchitect/Private");

		PublicDependencyModuleNames.AddRange(new string[]{
			// Base
			"Core", "CoreUObject", "Engine", "InputCore", "AppFramework",
			
			// Custom editor
			"UnrealEd", "DetailCustomizations", "PropertyEditor", "EditorStyle"
		});

		PrivateDependencyModuleNames.AddRange(new string[]{ "EditorScriptingUtilities",  "Slate", "SlateCore", "AITestSuite" });

	}
}
