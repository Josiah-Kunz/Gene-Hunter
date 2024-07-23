using UnrealBuildTool;

public class TopdownCharacter : ModuleRules{

	public TopdownCharacter(ReadOnlyTargetRules Target) : base(Target){

		PrivateIncludePaths.AddRange(new string[]{
			"TopdownCharacter/Private",
		});

		PublicIncludePaths.AddRange(new string[]{
			"TopdownCharacter/Public",
		});
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"CombatStatsComponent",
			"Engine",	// for ActorComponent.h (external)
			"LevelComponent",
			"PaperZD",	// it's the base class!
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for FStrings and such
			"CoreUObject",	// for UObjects
			"GHLibraries",	// for REQUIRE_COMPONENT and such
			  
		});
	}
}