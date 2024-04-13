using UnrealBuildTool;

public class DebuffComponent : ModuleRules{

	public DebuffComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/DebuffComponent/Private",
			"EffectComponentModules/DebuffComponent/Private/Debuffs",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/DebuffComponent/Public",
			"EffectComponentModules/DebuffComponent/Public/Debuffs",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",			// for SplitCamelCase
			"CombatStatsComponent", // we use UCombatStats on BrokenSoul
			"EffectComponent",		// for inheritance
			"TimedEffectComponent",	// for inheritance
			"GHLibraries",			// for component utilities SEARCH_FOR_COMPONENT
			"UI",					// for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}