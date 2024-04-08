using UnrealBuildTool;

public class DependentEffectComponent : ModuleRules{

	public DependentEffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/DependentEffectComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/DependentEffectComponent/Public",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries", // for SplitCamelCase
			"CombatStatsComponent",	// For PermStatMod
			"EffectComponent",		// We inherit from this!
			"GHLibraries", // for RequireComponent
			"UI",          // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}