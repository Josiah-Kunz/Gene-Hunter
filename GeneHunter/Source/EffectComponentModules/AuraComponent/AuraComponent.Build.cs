using UnrealBuildTool;

public class AuraComponent : ModuleRules{

	public AuraComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/AuraComponent/Private",
			"EffectComponentModules/AuraComponent/Private/Auras",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/AuraComponent/Public",
			"EffectComponentModules/AuraComponent/Public/Auras",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			"BPLibraries", // for SplitCamelCase
			"CombatStatsComponent",	// For Outlets
			"EffectComponent",	// for inheritance
			"GHLibraries",		// for component utilities SEARCH_FOR_COMPONENT
			"UI",				// for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for IMPLEMENT_MODULE
			"CoreUObject",	// for UObjects
			"Engine",		// for AActor
			
			// Libraries and utilities
			"CombatStatsComponent", // For Outlets
			"EffectComponent",	// for inheritance
			"BPLibraries",		// for SplitCamelCase
			"GHLibraries",		// for component utilities SEARCH_FOR_COMPONENT
			"UI", 				// for SupportingText
		});
	}
}