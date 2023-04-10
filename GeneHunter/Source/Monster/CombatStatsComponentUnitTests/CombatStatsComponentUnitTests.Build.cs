using UnrealBuildTool;

public class CombatStatsComponentUnitTests : ModuleRules{
	
	public CombatStatsComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/CombatStatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"					// for FString
		  , "CoreUObject"			// for UObjects (and their initializations)
		  , "Engine"				// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "CombatStatsComponent"	// for the type that we're testing
		  , "LevelComponent"		// goes with StatsComponent
		  , "GHLibraries",			// to create dummy worlds
		    "EffectComponent",		// we'll be testing Outlets too 
		    "UnrealEd", "NetcodeUnitTest",		// to get dummy unit test UWorlds
		});
	}
}