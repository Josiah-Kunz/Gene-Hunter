using UnrealBuildTool;

public class AffinitiesComponentUnitTests : ModuleRules{
	
	public AffinitiesComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"UnrealEd"        // to get dummy unit test UWorlds
		});
		
		PrivateIncludePaths.Add("Monster/AffinitiesComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "EffectComponent"			// for, e.g., DoublePoints unit test
		  , "AffinitiesComponent"		// b/c these are the thing we're testing
		  , "GHLibraries"				// to create dummy worlds
		  , "UnrealEd"					// to get dummy unit test UWorlds
		  , "NetcodeUnitTest"
		});
	}
}