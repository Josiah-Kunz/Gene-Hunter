using UnrealBuildTool;

public class EffectComponent : ModuleRules{

	public EffectComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.AddRange(new string[]{
			"Monster/EffectComponent/Public", "Monster/EffectComponent/Public"
		});

		PublicIncludePaths.AddRange(new string[]{
			"Monster/EffectComponent/Public", "Monster/EffectComponent/Public"
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"StatsComponent"	// for FStat in ModifyStat.h
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for IMPLEMENT_MODULE
			"CoreUObject",	// for UObjects
			"Engine",		// for DataAsset.h
		});
	}
}