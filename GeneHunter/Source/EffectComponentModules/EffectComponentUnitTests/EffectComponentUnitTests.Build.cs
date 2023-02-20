using UnrealBuildTool;

public class EffectComponentUnitTests : ModuleRules{
	
	public EffectComponentUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/StatsComponentUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "CombatStatsComponent"		// for UStatsComponent::GetStat
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		  , "EffectComponent"			// b/c these are the thing we're testing
		  , "AuraComponent"				// and these (for now: TODO)
		  , "GHLibraries"				// for the REQUIRE_COMPONENT macro
		  , "StatsComponentUnitTests"   // for stats' unit tests
		  , "LevelComponent"			// goes with StatsComponent
		   ,"MutationComponent"			// for BerserkerGene
		});
	}
}