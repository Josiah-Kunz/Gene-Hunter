using UnrealBuildTool;

public class MutationEffectComponent : ModuleRules{

	public MutationEffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/MutationEffectComponent/Private",
			"EffectComponentModules/MutationEffectComponent/Private/Mutations",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/MutationEffectComponent/Public",
			"EffectComponentModules/MutationEffectComponent/Public/Mutations",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",			// for SplitCamelCase
			"CombatStatsComponent", // for BerserkerGene
			"DependentEffectComponent",	// to use PermStatMod
			"EffectComponent",		// for inheritance
			"IntrinsicEffectComponent", // for inheritance
			"GHLibraries",			// for component utilities SEARCH_FOR_COMPONENT
			"UI", 					// for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}