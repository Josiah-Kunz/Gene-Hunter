using UnrealBuildTool;

public class BPLibraries : ModuleRules{

	public BPLibraries(ReadOnlyTargetRules Target) : base(Target){
		
		
		PrivateIncludePaths.Add("BPLibraries/Private");
		
		PublicIncludePaths.Add("BPLibraries/Public");
		
		//PublicDependencyModuleNames.AddRange(new string[]{ "UMG" });
		PrivateDependencyModuleNames.AddRange(new string[]{
			// Basic
			"Core"			// for FStrings (in, e.g., sorting assets)
		  , "CoreUObject"	// for UObjects
		  , "Engine"		// for UBlueprintFunctionLibrary
			
			// Editor
			, "EditorScriptingUtilities"	// AssetFunctionLibrary needs EditorAssetLibrary.h
			, "UMG"							// for WidgetFunctionLibrary
		});
	}
}