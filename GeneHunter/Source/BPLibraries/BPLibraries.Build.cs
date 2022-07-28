﻿using UnrealBuildTool;

public class BPLibraries : ModuleRules{

	public BPLibraries(ReadOnlyTargetRules Target) : base(Target){
		
		
		PrivateIncludePaths.Add("BPLibraries/Private");
		
		PublicIncludePaths.Add("BPLibraries/Public");
		
		PublicDependencyModuleNames.AddRange(new string[]{ "UMG" });
		PrivateDependencyModuleNames.AddRange(new string[]{
			// Basic
			"Core", "CoreUObject", "Engine"
			
			// Editor
			, "Slate", "SlateCore", "EditorScriptingUtilities"
		});
	}
}