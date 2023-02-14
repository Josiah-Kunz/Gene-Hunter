using UnrealBuildTool;

public class EffectableComponent : ModuleRules{
	
	public EffectableComponent(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("EffectableComponent/Private");
		PublicIncludePaths.Add("EffectableComponent/Public");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"Core"						// for FString
		  , "CoreUObject"				// for UObjects (and their initializations)
		  , "Engine"					// for UBlueprintFuncitonLibrary in StatUnitTestUtilities.h
		});
	}
}