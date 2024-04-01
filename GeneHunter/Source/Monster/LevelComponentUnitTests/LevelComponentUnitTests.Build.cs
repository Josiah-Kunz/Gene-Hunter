using UnrealBuildTool;

public class LevelComponentUnitTests : ModuleRules{
	
	public LevelComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"UnrealEd"				// to get dummy unit test UWorlds
			, "NetcodeUnitTest"		// UnchangeableBaseYield_UNITTEST.h needs this to be public since it has no .cpp
		});
		
		PrivateIncludePaths.Add("Monster/LevelComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
		   "AffinitiesComponent"		// for GetCXP (based on Type)
		  ,	"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "EffectComponent"			// for, e.g., DoublePoints unit test
		  , "LevelComponent"			// b/c these are the thing we're testing
		  , "GHLibraries"				// to create dummy worlds
		  , "NetcodeUnitTest"			// to get dummy unit test UWorlds
		  , "Types",					// for GetCXP (based on Type)
		    "TypesUnitTests",			// to get dummy Types
		    "UnrealEd"					// to get dummy unit test UWorlds
		});
	}
}