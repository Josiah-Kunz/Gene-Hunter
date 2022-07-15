// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GeneHunterEditor : ModuleRules // TODO: can this just inherit from GeneHunter ?
{
	public GeneHunterEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add("GeneHunterEditor/Public");
		PrivateIncludePaths.Add("GeneHunterEditor/Private");
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AppFramework", 
		// Custom editor:
		"UnrealEd", "DetailCustomizations", "PropertyEditor", "EditorStyle", "GeneHunter" });

		PrivateDependencyModuleNames.AddRange(new string[]{ "EditorScriptingUtilities",  "Slate", "SlateCore", "AITestSuite" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
