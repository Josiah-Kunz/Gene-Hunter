using UnrealBuildTool;

public class TypesUnitTests : ModuleRules{
	
	public TypesUnitTests(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/TypesUnitTests/Private");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"			// for FString
		  , "CoreUObject"	// for UObjects (and their initializations)
		  , "Engine"		// for UPrimaryDataAsset
		  , "BPLibraries"	// for RangeToString
		  , "Types"			// for UType
		  , "UI"			// for SupportingText.h
		  , "UMG"
		});
	}
}