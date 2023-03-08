using UnrealBuildTool;

public class HoTComponent : ModuleRules{

	public HoTComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/HoTComponent/Private",
			"EffectComponentModules/HoTComponent/Private/HoTs",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/HoTComponent/Public",
			"EffectComponentModules/HoTComponent/Public/HoTs",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",			// for SplitCamelCase
			"BuffComponent",		// for inheritance
			"CombatStatsComponent",	// because we're healing the FHealth over time
			"EffectComponent",		// for inheritance
			"GHLibraries",			// for component utilities SEARCH_FOR_COMPONENT
			"TimedEffectComponent",	// for inheritance
			"UI",					// for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"CombatStatsComponent", // because we're healing the FHealth over time
		});
	}
}