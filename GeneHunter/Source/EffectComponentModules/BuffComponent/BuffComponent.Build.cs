using UnrealBuildTool;

public class BuffComponent : ModuleRules{

	public BuffComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/BuffComponent/Private",
			"EffectComponentModules/BuffComponent/Private/Buffs",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/BuffComponent/Public",
			"EffectComponentModules/BuffComponent/Public/Buffs",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",			// for SplitCamelCase
			"CombatStatsComponent",	// for DimensionalShift.h
			"EffectComponent",		// for inheritance
			"TimedEffectComponent",	// for inheritance
			"GHLibraries",			// for component utilities SEARCH_FOR_COMPONENT
			"UI",					// for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}