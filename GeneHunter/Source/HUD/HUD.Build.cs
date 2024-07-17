using UnrealBuildTool;

public class HUD : ModuleRules{

	public HUD(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{
			
			// UI stuff
			"UMG", "Slate", "SlateCore",
			
			// Components
			"CombatStatsComponent",
		});

		PrivateIncludePaths.Add("HUD/Private");
		
		PublicIncludePaths.Add("HUD/Public");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for basic types
			"CoreUObject",	// to use UObjects
			"Engine",		// to use ActorComponents and such
			
			"GHLibraries",	// For finding components
			"UMG",
		}); 
	}
}