// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DetailsPanelArchitect : ModuleRules 
{
	public DetailsPanelArchitect(ReadOnlyTargetRules Target) : base(Target){



		PublicIncludePaths.Add("DetailsPanelArchitect/Public");
		PrivateIncludePaths.Add("DetailsPanelArchitect/Private");

		PublicDependencyModuleNames.AddRange(new string[]{
			"UnrealEd", "DetailCustomizations", "PropertyEditor", "EditorStyle"
		});

	}
}
