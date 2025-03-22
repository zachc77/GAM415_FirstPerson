// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM415_firstperson : ModuleRules
{
	public GAM415_firstperson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara"});
	}
}
