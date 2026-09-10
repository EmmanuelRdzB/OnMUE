// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OnMUE : ModuleRules
{
	public OnMUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks",
			"OnlineSubsystem", 
			"OnlineSubsystemUtils"
		});
		
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"OnMUE",
			"OnMUE/Variant_Horror",
			"OnMUE/Variant_Horror/UI",
			"OnMUE/Variant_Shooter",
			"OnMUE/Variant_Shooter/AI",
			"OnMUE/Variant_Shooter/UI",
			"OnMUE/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
