using UnrealBuildTool;

public class TalentEffectComponent : ModuleRules{

	public TalentEffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/TalentEffectComponent/Private",
			"EffectComponentModules/TalentEffectComponent/Private/TalentEffects",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/TalentEffectComponent/Public",
			"EffectComponentModules/TalentEffectComponent/Public/TalentEffects",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",				// for SplitCamelCase
			"CombatStatsComponent",		// we use UCombatStats on NaturalSelector
			"EffectComponent",			// for inheritance
			"IntrinsicEffectComponent",	// for inheritance
			"GHLibraries",				// for component utilities SEARCH_FOR_COMPONENT
			"UI",						// for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}