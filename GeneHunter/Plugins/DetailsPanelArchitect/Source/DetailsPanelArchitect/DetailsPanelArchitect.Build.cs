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
				"Slate",
				"SlateCore",
				
				// Editor specific
				"BPLibraries",		// ToSI functionality
				"CustomSlate",		// for custom slates like SStatsBar
				"EditorStyle",		// for, e.g., FEditorStyle::Get()
				"PropertyEditor",	// IDetailLayoutBuilder
				"Types",			// Type affinities
				"UI",				// SupportingText

				// Types to customize
				"AffinitiesComponent",
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
