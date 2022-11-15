// Shoot Em Up. Educational Project

using UnrealBuildTool;

public class ShootEmUp : ModuleRules
{
	public ShootEmUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
		});
	}
}
