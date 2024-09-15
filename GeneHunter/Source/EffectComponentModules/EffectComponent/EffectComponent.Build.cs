using UnrealBuildTool;

public class EffectComponent : ModuleRules{

	public EffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/EffectComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/EffectComponent/Public",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries", // for SplitCamelCase
			"CombatStatsComponent",	// For PermStatMod
			"EffectableComponent",	// EffectComponents themselves are effectable
			"GHLibraries", // for RequireComponent
			"UI",          // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"GHLibraries",	// for ComponentUtilities::bIsInUnitTestMode
		});
	}
}