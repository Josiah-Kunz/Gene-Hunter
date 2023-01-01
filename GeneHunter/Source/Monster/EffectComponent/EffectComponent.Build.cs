using UnrealBuildTool;

public class EffectComponent : ModuleRules{

	public EffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"Monster/EffectComponent/Private",
			"Monster/EffectComponent/Private/BaseClasses",
			"Monster/EffectComponent/Private/Effects",
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/EffectComponent/Public", 
			"Monster/EffectComponent/Public/BaseClasses",
			"Monster/EffectComponent/Public/Effects",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"StatsComponent",	// for FStat in ModifyStat.h
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for IMPLEMENT_MODULE
			"CoreUObject",	// for UObjects
			"Engine",		// for AActor
			"GHLibraries",	// for RequireComponent
			"BPLibraries",	// for SplitCamelCase
		});
	}
}