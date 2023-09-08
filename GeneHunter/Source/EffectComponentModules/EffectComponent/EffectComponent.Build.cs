using UnrealBuildTool;

public class EffectComponent : ModuleRules{

	public EffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/EffectComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/EffectComponent/Public",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"GHLibraries", // for RequireComponent
			"BPLibraries", // for SplitCamelCase
			"UI",          // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}