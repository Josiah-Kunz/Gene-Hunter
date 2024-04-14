using UnrealBuildTool;

public class TraitEffectComponent : ModuleRules{

	public TraitEffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/TraitEffectComponent/Private",
			"EffectComponentModules/TraitEffectComponent/Private/Traits",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/TraitEffectComponent/Public",
			"EffectComponentModules/TraitEffectComponent/Public/Traits",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",     // for SplitCamelCase
			"EffectComponent", // for inheritance
			"IntrinsicEffectComponent",	// for inheritance
			"GHLibraries",     // for component utilities SEARCH_FOR_COMPONENT
			"UI",              // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}