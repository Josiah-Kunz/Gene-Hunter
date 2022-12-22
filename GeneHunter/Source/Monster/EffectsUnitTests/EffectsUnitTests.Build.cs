using UnrealBuildTool;

public class EffectsUnitTests : ModuleRules{
	
	public EffectsUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/StatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "StatsComponent"			// for stats unit tests
		  , "StatsComponentUnitTests"	// ...and their unit tests
		});
	}
}