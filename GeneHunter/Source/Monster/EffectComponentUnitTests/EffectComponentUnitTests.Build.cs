using UnrealBuildTool;

public class EffectComponentUnitTests : ModuleRules{
	
	public EffectComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/StatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "EffectComponent"			// b/c these are the thing we're testing
		  , "StatsComponent"			// for stats unit tests
		  , "StatsComponentUnitTests"	// ...and their unit tests
		});
	}
}