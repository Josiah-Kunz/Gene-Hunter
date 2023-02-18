using UnrealBuildTool;

public class IntrinsicEffectComponent : ModuleRules{

	public IntrinsicEffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/IntrinsicEffectComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/IntrinsicEffectComponent/Public",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",     // for SplitCamelCase
			"EffectComponent", // for inheritance
			"GHLibraries",     // for component utilities SEARCH_FOR_COMPONENT
			"UI",              // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}