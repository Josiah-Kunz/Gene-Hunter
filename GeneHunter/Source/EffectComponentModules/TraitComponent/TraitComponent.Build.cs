using UnrealBuildTool;

public class TraitComponent : ModuleRules{

	public TraitComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/TraitComponent/Private",
			"EffectComponentModules/TraitComponent/Private/Traits",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/TraitComponent/Public",
			"EffectComponentModules/TraitComponent/Public/Traits",
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