using UnrealBuildTool;

public class HoTComponent : ModuleRules{

	public HoTComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"EffectComponentModules/HoTComponent/Private",
			"EffectComponentModules/HoTComponent/Private/HoTs",
		});

		PublicIncludePaths.AddRange(new string[]{
			"EffectComponentModules/HoTComponent/Public",
			"EffectComponentModules/HoTComponent/Public/HoTs",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",        // for IMPLEMENT_MODULE
			"CoreUObject", // for UObjects
			"Engine",      // for AActor
			
			// Libraries and utilities
			"BPLibraries",     // for SplitCamelCase
			"EffectComponent", // for inheritance
			"BuffComponent",// for inheritance
			"GHLibraries",     // for component utilities SEARCH_FOR_COMPONENT
			"UI",              // for SupportingText
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		});
	}
}