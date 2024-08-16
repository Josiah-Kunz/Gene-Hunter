using UnrealBuildTool;

public class CombatStatsComponentUnitTests : ModuleRules{
	
	public CombatStatsComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"UnrealEd"        // to get dummy unit test UWorlds
		  , "NetcodeUnitTest" // some unit tests need this to be public since they have no .cpp
		});
		
		PrivateIncludePaths.Add("Monster/CombatStatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		  "AffinitiesComponent",	// damage formula testing needs type advantages
		  "BattleEngine",			// cuz we do some damage formula testing
		  "Core",					// for FString
		  "CoreUObject",			// for UObjects (and their initializations)
		  "EffectComponent",		// we'll be testing Outlets too 
		  "Engine",					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  "CombatStatsComponent",	// for the type that we're testing
		  "GHLibraries",			// to create dummy worlds
		  "LevelComponent",			// goes with StatsComponent
		  "Types",					// to get dummy UTypes
		  "TypesUnitTests",			// to get dummy UTypes
		  "UnrealEd",				// to get dummy unit test UWorlds
		  "NetcodeUnitTest",
		});
	}
}