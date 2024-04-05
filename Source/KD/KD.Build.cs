using UnrealBuildTool;

public class KD : ModuleRules
{
    public KD(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UnrealEd", "ProceduralMeshComponent", "DeveloperSettings", "EnhancedInput", "Networking", "CommonUI", "UMG" });
    }

}

