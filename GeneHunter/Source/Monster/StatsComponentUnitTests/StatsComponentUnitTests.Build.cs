using UnrealBuildTool;

public class StatsComponentUnitTests : ModuleRules{
	
	public StatsComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/StatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"			// for FString
		  , "CoreUObject"	// for UObjects (and their initializations)
		  , "Engine"		// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "StatsComponent"	// for the type that we're testing
		  , "LevelComponent"	// goes with StatsComponent
		});
	}
}