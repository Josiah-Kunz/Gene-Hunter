// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GeneHunterEditorTarget : TargetRules
{
	public GeneHunterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		//ExtraModuleNames.Add("GeneHunter");
		ExtraModuleNames.AddRange(new []{"GeneHunter", "DetailsPanelArchitect"});
	}
}
