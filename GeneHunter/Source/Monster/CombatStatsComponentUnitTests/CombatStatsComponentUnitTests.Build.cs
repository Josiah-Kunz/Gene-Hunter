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
		  "CombatStatsComponent",	// for the type that we're testing
		  "Core",					// for FString
		  "CoreUObject",			// for UObjects (and their initializations)
		  "EffectComponent",		// we'll be testing Outlets too 
		  "Engine",					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  "GHLibraries",			// to create dummy worlds
		  "HoTComponent",			// used to test EffectAttachment
		  "LevelComponent",			// goes with StatsComponent
		  "NetcodeUnitTest",		// needed for unit tests
		  "Types",					// to get dummy UTypes
		  "TypesUnitTests",			// to get dummy UTypes
		  "UnrealEd",				// to get dummy unit test UWorlds
		});
	}
}