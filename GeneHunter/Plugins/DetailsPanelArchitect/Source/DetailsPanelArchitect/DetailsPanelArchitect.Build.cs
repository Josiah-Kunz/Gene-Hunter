// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DetailsPanelArchitect : ModuleRules
{
	public DetailsPanelArchitect(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// Basics
				"Core",
				
				// Editor specific
				"PropertyEditor",	// IDetailLayoutBuilder
				"BPLibraries",		// ToSI functionality
				"UI",				// SupportingText

				// Types to customize
				"StatsComponent",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				
				// Basics
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
