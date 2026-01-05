// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FP_DialogueSystem : ModuleRules
{
	public FP_DialogueSystem(ReadOnlyTargetRules Target) : base(Target)
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
			"Json",
			"JsonUtilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FP_DialogueSystem",
			"FP_DialogueSystem/Variant_Horror",
			"FP_DialogueSystem/Variant_Horror/UI",
			"FP_DialogueSystem/Variant_Shooter",
			"FP_DialogueSystem/Variant_Shooter/AI",
			"FP_DialogueSystem/Variant_Shooter/UI",
			"FP_DialogueSystem/Variant_Shooter/Weapons",
			"FP_DialogueSystem/DialogueSystem"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
