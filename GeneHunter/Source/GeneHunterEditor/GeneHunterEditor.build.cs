// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GeneHunterEditor : GeneHunter 
{
	public GeneHunterEditor(ReadOnlyTargetRules Target) : base(Target){

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add("GeneHunterEditor/Public");
		PrivateIncludePaths.Add("GeneHunterEditor/Private");

		PublicDependencyModuleNames.AddRange(new string[]{
			"UnrealEd"
		  , "DetailCustomizations", "PropertyEditor", "EditorStyle", "GeneHunter"
		});

	}
}
