using UnrealBuildTool;

public class EffectComponent : ModuleRules{

	public EffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/EffectComponent/Private",
			"EffectComponentModules/EffectComponent/Private/BaseClasses",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/EffectComponent/Public", 
			"EffectComponentModules/EffectComponent/Public/BaseClasses",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"GHLibraries", // for RequireComponent
			"BPLibraries", // for SplitCamelCase
			"UI",          // for SupportingText
			
			"CombatStatsComponent" // TODO: we only need this for UHoT, etc.
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}