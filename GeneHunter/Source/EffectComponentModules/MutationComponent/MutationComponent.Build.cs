using UnrealBuildTool;

public class MutationComponent : ModuleRules{

	public MutationComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/MutationComponent/Private",
			"EffectComponentModules/MutationComponent/Private/Mutations",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/MutationComponent/Public",
			"EffectComponentModules/MutationComponent/Public/Mutations",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",     // for SplitCamelCase
			"EffectComponent", // for inheritance
			"IntrinsicEffectComponent", // for inheritance
			"GHLibraries",     // for component utilities SEARCH_FOR_COMPONENT
			"UI",              // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}