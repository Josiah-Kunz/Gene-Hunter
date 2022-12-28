using UnrealBuildTool;

public class Effects : ModuleRules{

	public Effects(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/Effects/Private");
		
		PublicIncludePaths.Add("Monster/Effects/Public");
		
		PublicDependencyModuleNames.AddRange(new string[]{ }); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for IMPLEMENT_MODULE
			"CoreUObject",	// for UObjects
			"Engine",		// for DataAsset.h
		});
	}
}