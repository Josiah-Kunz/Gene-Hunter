using UnrealBuildTool;

public class NegativeAuraComponent : ModuleRules{

	public NegativeAuraComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/NegativeAuraComponent/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/NegativeAuraComponent/Public",
			"EffectComponentModules/NegativeAuraComponent/Public/NegativeAuras",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"AuraComponent",   // for inheritance
			"BPLibraries",     // for SplitCamelCase
			"EffectComponent", // for inheritance
			"GHLibraries",     // for component utilities SEARCH_FOR_COMPONENT
			"UI",              // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}