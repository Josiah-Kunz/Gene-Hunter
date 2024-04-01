﻿using UnrealBuildTool;

public class CombatStatsComponentUnitTests : ModuleRules{
	
	public CombatStatsComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"UnrealEd"        // to get dummy unit test UWorlds
		  , "NetcodeUnitTest" // some unit tests need this to be public since they have no .cpp
		});
		
		PrivateIncludePaths.Add("Monster/CombatStatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"					// for FString
		  , "CoreUObject"			// for UObjects (and their initializations)
		  , "Engine"				// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "CombatStatsComponent"	// for the type that we're testing
		  , "LevelComponent"		// goes with StatsComponent
		  , "GHLibraries",			// to create dummy worlds
		    "EffectComponent",		// we'll be testing Outlets too 
		    "UnrealEd"				// to get dummy unit test UWorlds
		  , "NetcodeUnitTest"
		});
	}
}