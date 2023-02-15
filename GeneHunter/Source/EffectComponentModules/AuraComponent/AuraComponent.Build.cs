using UnrealBuildTool;

public class AuraComponent : ModuleRules{

	public AuraComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/AuraComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/AuraComponent/Public",
			"EffectComponentModules/AuraComponent/Public/Auras",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"CombatStatsComponent",
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for IMPLEMENT_MODULE
			"CoreUObject",	// for UObjects
			"Engine",		// for AActor
			
			// Libraries and utilities
			"EffectComponent",	// for inheritance
			"BPLibraries",		// for SplitCamelCase
			"GHLibraries",		// for component utilities SEARCH_FOR_COMPONENT
			"UI", 				// for SupportingText
		});
	}
}