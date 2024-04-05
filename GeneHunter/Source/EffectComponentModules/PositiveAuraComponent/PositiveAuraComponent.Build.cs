using UnrealBuildTool;

public class PositiveAuraComponent : ModuleRules{

	public PositiveAuraComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/PositiveAuraComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/PositiveAuraComponent/Public",
			"EffectComponentModules/PositiveAuraComponent/Public/PositiveAuras",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"AuraComponent",   // for inheritance
			"BPLibraries",     // for SplitCamelCase
			"CombatStatsComponent", // we use UCombatStats on FullBloom
			"EffectComponent", // for inheritance
			"GHLibraries",     // for component utilities SEARCH_FOR_COMPONENT
			"UI",              // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}