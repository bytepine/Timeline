using UnrealBuildTool;

public class TimelineEditor : ModuleRules
{
    public TimelineEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Timeline",
                "AssetTools",
                "UnrealEd",
                "AdvancedPreviewScene",
            }
        );
    }
}