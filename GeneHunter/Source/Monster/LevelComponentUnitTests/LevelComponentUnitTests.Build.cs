using UnrealBuildTool;

public class LevelComponentUnitTests : ModuleRules{
	
	public LevelComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/LevelComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "EffectComponent"			// for, e.g., DoublePoints unit test
		  , "LevelComponent"			// b/c these are the thing we're testing
		  , "GHLibraries"				// to create dummy worlds
		  , "AffinitiesComponent"		// for GetCXP (based on Type)
		  , "Types",					// for GetCXP (based on Type)
		    "TypesUnitTests",			// to get dummy Types
		});
	}
}