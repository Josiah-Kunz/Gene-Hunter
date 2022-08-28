﻿using UnrealBuildTool;

public class Types : ModuleRules{

	public Types(ReadOnlyTargetRules Target) : base(Target){
		
		PrivateIncludePaths.Add("Monster/Types/Private");
		
		PublicIncludePaths.Add("Monster/Types/Public");
		
		PublicDependencyModuleNames.AddRange(new string[]{
			"UI"			// for SupportingText.h
		  , "BPLibraries"	// for SortAssetsAlphabetically
		}); 
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			
			// Basics
			"Core",			// for FStrings and such
			"CoreUObject",	// for UObjects
			"Engine",		// for UPrimaryDataAsset
			"EditorStyle",	// for, e.g., FEditorStyle::Get()
			"Slate",		// for SButton
			"SlateCore",	// for SCompoundWidget
			  
			// Other modules
			"BPLibraries",	// for SortAssetsAlphabetically
			"UMG",			// for UComboBoxString
		});
	}
}