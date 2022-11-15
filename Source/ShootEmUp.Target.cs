// Shoot Em Up. Educational Project

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootEmUpTarget : TargetRules
{
	public ShootEmUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootEmUp" } );
		WindowsPlatform.PCHMemoryAllocationFactor = 2000;
	}
}
