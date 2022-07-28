using UnrealBuildTool;

public class StatsBlockUnitTests : ModuleRules{
	
	public StatsBlockUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/StatsBlockUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"			// for FString
		  , "CoreUObject"	// for UObjects (and their initializations)
		  , "Engine"		// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  //, "BPLibraries"	// for RangeToString
		  , "StatsBlock"	// for the type that we're testing
		});
	}
}