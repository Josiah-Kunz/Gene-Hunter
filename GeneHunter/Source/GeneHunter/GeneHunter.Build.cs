// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GeneHunter : ModuleRules
{
	public GeneHunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]{
			// Base
			"Core", "CoreUObject", "Engine", "InputCore", "AppFramework"
			
			// Custom editor
			, "UnrealEd", "DetailCustomizations", "PropertyEditor", "EditorStyle"
			  
			  // Should these be private?
			, "EditorScriptingUtilities",  "Slate", "SlateCore", "AITestSuite"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
