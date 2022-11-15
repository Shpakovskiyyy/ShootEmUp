// Shoot Em Up. Educational Project

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootEmUpEditorTarget : TargetRules
{
	public ShootEmUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootEmUp" } );
	}
}
